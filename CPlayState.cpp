// Last updated: 22.02.16

#include "Globals.h"
#include "CGameStateHandler.h"
#include "CPlayState.h"
#include "CLoadScreen.h"
#include "MessageQueue.h"
#include "CBulletFactory.h"
#include <iostream>
#include <sstream>

// controllers are in this.
using namespace NETTIK;

CPlayState CPlayState::mPlayState;

CEnemyManager* CPlayState::GetEnemyManager()
{
	return mEnemyManager.get();
}

void CPlayState::SetNetwork(ENetworkType type)
{
	mNetworkType = type;
}

void CPlayState::InitNetwork()
{

	if (mPNetwork != 0)
		delete(mPNetwork);

	// build the gamenetwork
	mPNetwork = GameNetwork::Instance();
	mPNetwork->InitNETTIK(mNetworkType);
	mPNetwork->GetController<IController>()->CreateInstance("game");
	mPNetwork->Init();

	// setup connection details.
	bool connectionStatus = false;

	if (mNetworkType == kNetworkClient)
		connectionStatus = mPNetwork->GetController<IControllerClient>()->Connect(NET_HOST.c_str(), NET_PORT);
	else if (mNetworkType == kNetworkServer)
		connectionStatus = mPNetwork->GetController<IControllerServer>()->Listen(NET_PORT, NET_PLAYERS - 1); // take one away for the server being a "player"
	else
		throw std::exception("ENetworkType invalid.");

	if (!connectionStatus)
	{
		// Some sort of message box here.
		cout << "Failed to initialise network controller, server offline? Hostname in use?" << endl;
		return;
	}

	mPNetwork->GetController<IController>()->Start();
}

void CPlayState::InitLives()
{
	// Draw life sprites
	for (int i = 0; i < mPNetwork->GetPlayerFactory().GetLocalPlayer()->GetLives(); i++)
	{
		float startPosX = 505;
		float startPosY = 932;
		float startPosInc = 35;
		ISprite* temp = gEngine->CreateSprite("life.png", startPosX + startPosInc * static_cast<float>(i), startPosY, 0.09f);
		mLifeSprites.push_back(temp);
		gEngine->DrawScene();
	}
}

void CPlayState::Init()
{
	// LOADING SCREEN
	CLoadScreen* loadScreen = new CLoadScreen();

	gEngine->DrawScene();

	// GRAPHICS
	mFloorMesh = gEngine->LoadMesh(GROUND_MESH);
	for (int i = 0; i < kFloorAmount; i++)
	{
		mFloor.push_back(mFloorMesh->CreateModel(-6.0f, -1000.0f, kFloorStart + (kFloorSize * i)));
		mFloor.at(i)->SetSkin(METAL_TEX);
	}

	// UI
	mUI = gEngine->CreateSprite(UI, 0.0f, 0.0f, 0.2f);
	mUI2 = gEngine->CreateSprite(UI2, 0.0f, 0.0f, 0.1f);

	mCam = gEngine->CreateCamera(kManual, 0.0f, 200.0f, 0.0f);
	mCam->RotateLocalX(90.0f);

	mpHealthBar = gEngine->CreateSprite("healthbar.png", kStartBarPosX, kStartBarPosY, 0.15f);
	mpShieldBar = gEngine->CreateSprite("shieldbar.png", kStartBarPosX, kStartBarPosY + 37.0f, 0.15f);

	//Text
	mFont = gEngine->LoadFont("Rockwell", 60U);

	// Start up the network controller.
	InitNetwork();

	// Bullet lists
	CBulletFactory::Instance()->GetBulletLists(mPBullets, mEBullets);

	// AI
	mEnemyManager.reset(new CEnemyManager("level0.txt"));
	mEnemyManager->SetLists(&mPNetwork->GetPlayerFactory().GetList(), mPBullets, mEBullets);
	
	// Particles
	mExplosions = CExplosionPool::Instance();
	mExplosions->Init();

	//Preload any assets at the start before they are needed

	gEngine->AddToLoadQueue(F16_ENEMY_MESH, 30);
	gEngine->AddToLoadQueue(HAVOC_BOSS_MESH);
	gEngine->AddToLoadQueue(MISSILE_MESH);
	gEngine->AddToLoadQueue(PARTICLE_MODEL, 10, SHOTGUN_POWER_UP);
	gEngine->AddToLoadQueue(PARTICLE_MODEL, 10, LASER_POWER_UP);
	gEngine->AddToLoadQueue(PARTICLE_MODEL, 10, UPGRADE_POWER_UP);

	for (int i = 1; i <= 10; ++i)
	{
		//Preload 200 of each of the smoke particles
		gEngine->AddToLoadQueue(PARTICLE_MODEL, 200, "Smoke" + to_string(i) + ".png");
	}

	// SOUND
	if (!mBufferShoot.loadFromFile(SOUND_SHOOT))
	{
		cout << "CPlayState.cpp: Error loading sound file" << endl;
	}

	mSound.setBuffer(mBufferShoot);
	mSound.setVolume(30.0f);

	//Load all queued objects and update the load screen with progress
	gEngine->LoadQueuedObjects(loadScreen);
	delete loadScreen;

	//Reset timer after finished loading assets
	gEngine->Timer();

	// Player
	if (mPNetwork->GetType() == kNetworkServer)
	{
		CPlayerFactory& factory = mPNetwork->GetPlayerFactory();
		factory.CreateLocalPlayer();

		InitLives();
	}
}

void CPlayState::Cleanup()
{
	gEngine->RemoveSprite(mUI);
	gEngine->RemoveCamera(mCam);
	for(auto& item : mFloor) mFloorMesh->RemoveModel(item);
	gEngine->RemoveMesh(mFloorMesh);
	mPBullets->clear();
	mEBullets->clear();
	mEnemyManager.reset();
	mExplosions->CleanUp();

	gEngine->RemoveFont(mFont);
	for (int i = 0; i < static_cast<int>(mLifeSprites.size()); i++)
	{
		gEngine->RemoveSprite(mLifeSprites[i]);
	}
	mLifeSprites.clear();
	gEngine->RemoveSprite(mpHealthBar);
	gEngine->RemoveSprite(mpShieldBar);

	// Must be after bullet cleanup. Bullet mesh
	// needs to exist to remove bullet models. 
	// Bullet mesh is owned by player.
	// mPlayer1.Cleanup();

	//Clear player list
	// mPlayerList.clear();
	
	// 10.04.16: Above code now gets called in CPlayerFactory destructor.
	
	// Close network connections, cleans factory data.
	if (mPNetwork != 0)
		mPNetwork->Stop();

	//Clear the cache of particles and other preloaded models/meshes
	gEngine->ClearModelCache();
	gEngine->ClearMeshCache();

}

void CPlayState::Pause() {}

void CPlayState::Resume() {}

void CPlayState::HandleEvents(CGameStateHandler * game)
{
	// Keypresses go here


	if (gEngine->KeyHit(KEY_EXIT))
	{
		game->Quit();
	}
}

void CPlayState::Update(CGameStateHandler * game)
{
	mDelta = gEngine->Timer();

	// Animations go here

	CPlayer* pLocalPlayer;
	pLocalPlayer = mPNetwork->GetPlayerFactory().GetLocalPlayer();

	if (mPNetwork->GetType() == kNetworkServer)
	{
		CPlayerFactory::PlayerList& players = mPNetwork->GetPlayerFactory().GetList();

		for (auto player : players)
		{
			player->CheckCollision();
		}

	}

	mEnemyManager->Update(mDelta);

	mExplosions->Update(mDelta);

	//Update all player projectiles
	for (auto bullet = mPBullets->begin(); bullet != mPBullets->end(); )
	{
		(*bullet)->Update(mDelta);

		if ((*bullet)->IsOutOfBounds())
		{
			(*bullet)->Cleanup();
			bullet = mPBullets->erase(bullet);
		}
		else
		{
			bullet++;
		}
	}

	//Update all enemy projectiles
	for (auto bullet = mEBullets->begin(); bullet != mEBullets->end(); )
	{
		(*bullet)->Update(mDelta);
		(*bullet)->CheckCollision();

		if ((*bullet)->IsOutOfBounds() || (*bullet)->IsDead())
		{
			(*bullet)->Cleanup();
			bullet = mEBullets->erase(bullet);
		}
		else
		{
			bullet++;
		}
	}

	/*if (gEngine->KeyHeld(KEY_FIRE)) //Needs moving into CWeapon
	{
		if (mSound.getStatus() == sf::SoundSource::Stopped)
		{
			mSound.play();
		}
	}*/

	// Move floor
	for (auto& item : mFloor)
	{
		item->MoveLocalZ(kFloorSpeed * mDelta);
	}

	// Message queue
	SMessage msg;
	CMessageQueue::Instance()->Fetch("events", msg);

	while (msg.type != kMessageInvalid)
	{
		CPlayer* player;

		switch (msg.type)
		{
		case kMessagePlayerInit:
			player = dynamic_cast<CPlayer*>(msg.entity);

			if (player)
			{
				player->Init();
				player->SetLists(mPBullets, mEBullets);
			}
			break;

		case kMessagePlayerCleanup:
			player = dynamic_cast<CPlayer*>(msg.entity);

			if (player)
			{
				player->Cleanup();
				delete(player);
			}
			break;
		}
		CMessageQueue::Instance()->Fetch("events", msg);
	}

	// Suspend following code.
	if (pLocalPlayer == nullptr)
	{
		// Try to find local player.
		pLocalPlayer = mPNetwork->GetPlayerFactory().GetLocalPlayer();

		if (pLocalPlayer == nullptr)
			return;
		else
			InitLives();
	}

	pLocalPlayer->Move(mDelta);

	if(pLocalPlayer->IsDead())
	{
		pLocalPlayer->LoseLife();

		//If the player has another life then start the new life

		if (mLifeSprites.size() > 0)
		{
			gEngine->RemoveSprite(mLifeSprites.back());
			mLifeSprites.pop_back();

			mpHealthBar->SetX(kStartBarPosX);
			mpShieldBar->SetX(kStartBarPosX);
		}
		else
		{
			//No more lives, so end the game
			//End the game
		}
	}

	DrawText();

	//Health Bars
	AnimateShield(mDelta);
	AnimateHealth(mDelta);

}


void CPlayState::DrawText()
{

	CPlayer* pLocalPlayer;
	pLocalPlayer = mPNetwork->GetPlayerFactory().GetLocalPlayer();

	if (pLocalPlayer == nullptr)
		return;

	stringstream textOut;
	//textOut.precision(2);
	textOut << pLocalPlayer->GetScore();
	mFont->Draw(textOut.str(), 1005, 940, kYellow);
}

void CPlayState::AnimateHealth(float delta)
{
	CPlayer* pLocalPlayer;
	pLocalPlayer = mPNetwork->GetPlayerFactory().GetLocalPlayer();

	if (pLocalPlayer == nullptr)
		return;

	//Find the proportion of the bar that should be filled
	float ratio = static_cast<float>(pLocalPlayer->GetHealth()) / static_cast<float>(pLocalPlayer->GetMaxHealth());

	//Find the x position the bar needs to be
	float target = static_cast<float>(kStartBarPosX) - kBarSize + ratio * kBarSize;

	//Move the bar towards the required position
	if (target > mpHealthBar->GetX())
	{
		float newLoc = min(target, mpHealthBar->GetX() + (delta * kBarSpeed));
		mpHealthBar->SetX(newLoc);
	}
	else
	{
		float newLoc = max(target, mpHealthBar->GetX() - (delta * kBarSpeed));
		mpHealthBar->SetX(newLoc);
	}
}

void CPlayState::AnimateShield(float delta)
{
	CPlayer* pLocalPlayer;
	pLocalPlayer = mPNetwork->GetPlayerFactory().GetLocalPlayer();

	if (pLocalPlayer == nullptr)
		return;

	//Find the proportion of the bar that should be filled
	float ratio = static_cast<float>(pLocalPlayer->GetShield()) / static_cast<float>(pLocalPlayer->GetMaxShield());

	//Find the x position the bar needs to be
	float target = static_cast<float>(kStartBarPosX) - kBarSize + ratio * kBarSize;

	//Move the bar towards the required position
	if (target > mpShieldBar->GetX())
	{
		float newLoc = min(target, mpShieldBar->GetX() + (delta * kBarSpeed));
		mpShieldBar->SetX(newLoc);
	}
	else
	{
		float newLoc = max(target, mpShieldBar->GetX() - (delta * kBarSpeed));
		mpShieldBar->SetX(newLoc);
	}
}

void CPlayState::Draw(CGameStateHandler * game)
{
	// Draw the scene
	gEngine->DrawScene();
}

