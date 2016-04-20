// Last updated: 22.02.16

#include "Globals.h"
#include "CGameStateHandler.h"
#include "CPlayState.h"
#include "CPausedState.h"
#include "CLoadScreen.h"
#include <iostream>
#include <sstream>

CPlayState CPlayState::mPlayState;

const float kLifeSpritePosX = 505;
const float kLifeSpritePosY = 932;
const float kLifeSpritePosZ = 0.09;
const float kLifeSpritePosInc = 35;

void CPlayState::Init()
{
	// LOADING SCREEN
	CLoadScreen* loadScreen = new CLoadScreen();

	gEngine->DrawScene();

	// GRAPHICS
	mFloorMesh = gEngine->LoadMesh(GROUND_MESH);
	for (int i = 0; i < kFloorAmount; i++)
	{
		mFloor.push_back(mFloorMesh->CreateModel(-6.0f, -1000.0f, kFloorStart + ((kFloorSize - 1.0f) * i)));
		mFloor.at(i)->SetSkin(METAL_TEX);
	}

	mClouds.reset(new CClouds());

	// Player
	mPlayer1.Init();
	mPlayer1.SetLists(&mPBullets, &mEBullets);
	mPlayerList.push_back(&mPlayer1);

	// UI
	mUI = gEngine->CreateSprite(UI, 0.0f, 0.0f, 0.2f);
	mUI2 = gEngine->CreateSprite(UI2, 0.0f, 0.0f, 0.1f);

	mCam = gEngine->CreateCamera(kManual, 0.0f, 200.0f, 0.0f);
	mCam->RotateLocalX(90.0f);

	mpHealthBar = gEngine->CreateSprite("healthbar.png", kStartBarPosX, kStartBarPosY, 0.15f);
	mpShieldBar = gEngine->CreateSprite("shieldbar.png", kStartBarPosX, kStartBarPosY + 37.0f, 0.15f);

	// Draw life sprites
	for (int i = 0; i < mPlayer1.GetLives(); i++)
	{
		ISprite* temp = gEngine->CreateSprite("life.png", kLifeSpritePosX + kLifeSpritePosInc * static_cast<float>(i), kLifeSpritePosY, kLifeSpritePosZ);
		mLifeSprites.push_back(temp);
		gEngine->DrawScene();
	}

	//Text
	mFont = gEngine->LoadFont("Rockwell", 60U);

	// AI
	mEnemyManager.reset(new CEnemyManager("level0.txt"));
	mEnemyManager->SetLists(&mPlayerList, &mPBullets, &mEBullets);
	
	// Particles
	mExplosions = CExplosionPool::Instance();
	mExplosions->Init();

	//Preload any assets at the start before they are needed

	gEngine->AddToLoadQueue(F16_ENEMY_MESH, 30);
	gEngine->AddToLoadQueue(HAVOC_BOSS_MESH, 1);
	gEngine->AddToLoadQueue(HALO_BOSS_MESH, 1);
	gEngine->AddToLoadQueue(MISSILE_MESH, 50);
	gEngine->AddToLoadQueue(BULLET_MESH, 100);
	gEngine->AddToLoadQueue(PARTICLE_MODEL, 10, SHOTGUN_POWER_UP);
	gEngine->AddToLoadQueue(PARTICLE_MODEL, 10, LASER_POWER_UP);
	gEngine->AddToLoadQueue(PARTICLE_MODEL, 10, UPGRADE_POWER_UP);
	gEngine->AddToLoadQueue(PARTICLE_MODEL, 10, HEALTH_POWER_UP);
	gEngine->AddToLoadQueue(PARTICLE_MODEL, 10, LIFE_POWER_UP);
	
	//Preload 200 of each of the smoke particles
	for (int i = 1; i <= 10; ++i)
	{
		gEngine->AddToLoadQueue(PARTICLE_MODEL, 200, "Smoke" + to_string(i) + ".png");
	}

	//Load all queued objects and update the load screen with progress
	gEngine->LoadQueuedObjects(loadScreen);
	delete loadScreen;

	if (!mMusic) //If it doesn't already exist
	{
		mMusic = gEngine->CreateMusic( GAME_MUSIC );
		mMusic->Play();
	}

	//Reset timer after finished loading assets
	gEngine->Timer();
}

void CPlayState::Cleanup()
{
	gEngine->RemoveCamera(mCam);

	//Remove the floor models then clear the vector of empty pointers
	for(auto& item : mFloor) mFloorMesh->RemoveModel(item);
	mFloor.clear();

	gEngine->RemoveMesh(mFloorMesh);
	mPBullets.clear();
	mEBullets.clear();
	mClouds.reset();
	mEnemyManager.reset();
	mExplosions->CleanUp();

	gEngine->RemoveFont(mFont);

	//Remove the life sprites then clear the vector of empty pointers
	for (auto& item : mLifeSprites) gEngine->RemoveSprite(item);
	mLifeSprites.clear();

	//Clean up UI
	gEngine->RemoveSprite(mUI);
	gEngine->RemoveSprite(mUI2);
	gEngine->RemoveSprite(mpHealthBar);
	gEngine->RemoveSprite(mpShieldBar);

	//Clean up player
	mPlayer1.Cleanup();

	//Clear player list
	mPlayerList.clear();

	//Clear the cache of particles and other preloaded models/meshes
	gEngine->ClearModelCache();
	gEngine->ClearMeshCache();

	mMusic->Stop();
}

void CPlayState::Pause() {}

void CPlayState::Resume() {}

void CPlayState::HandleEvents(CGameStateHandler * game)
{
	// Keypresses go here
	if (gEngine->KeyHit(KEY_PAUSE))
	{
		game->PushState(CPausedState::Instance());
	}

	if (gEngine->KeyHit(KEY_EXIT))
	{
		game->Quit();
	}
}

void CPlayState::Update(CGameStateHandler * game)
{
	mDelta = gEngine->Timer();

	// Animations go here

	// Restart music if coming from new game
	if (mMusic->GetStatus() == sf::SoundSource::Stopped)
	{
		mMusic->Play();
	}

	mPlayer1.Move(mDelta);
	mPlayer1.CheckCollision();

	mClouds->Move( mDelta );

	/*if (gEngine->KeyHeld(KEY_FIRE)) //Needs moving into CWeapon
	{
		if (mSound.getStatus() == sf::SoundSource::Stopped)
		{
			mSound.play();
		}
	}*/

	mEnemyManager->Update(mDelta);

	mExplosions->Update(mDelta);

	//Update all player projectiles
	for (auto bullet = mPBullets.begin(); bullet != mPBullets.end(); )
	{
		(*bullet)->Update(mDelta);

		if ((*bullet)->IsOutOfBounds())
		{
			bullet = mPBullets.erase(bullet);
		}
		else
		{
			bullet++;
		}
	}

	//Update all enemy projectiles
	for (auto bullet = mEBullets.begin(); bullet != mEBullets.end(); )
	{
		(*bullet)->Update(mDelta);
		(*bullet)->CheckCollision();

		if ((*bullet)->IsOutOfBounds() || (*bullet)->IsDead())
		{
			bullet = mEBullets.erase(bullet);
		}
		else
		{
			bullet++;
		}
	}

	// Move floor
	for (auto& item : mFloor)
	{
		item->MoveLocalZ(kFloorSpeed * mDelta);
	}

	//If the player gains a life, add a new life sprite
	//Unfortunately there isn't an easy way to do this event driven so we'll just check every frame instead
	while (mPlayer1.GetLives() > static_cast<int>(mLifeSprites.size()))
	{
		ISprite* temp = gEngine->CreateSprite("life.png", kLifeSpritePosX + kLifeSpritePosInc * static_cast<float>(mLifeSprites.size()), kLifeSpritePosY, kLifeSpritePosZ);
		mLifeSprites.push_back(temp);
		gEngine->DrawScene();
	}

	if(mPlayer1.IsDead())
	{
		mPlayer1.LoseLife();

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
	stringstream textOut;
	//textOut.precision(2);
	textOut << mPlayer1.GetScore();
	mFont->Draw(textOut.str(), 1005, 940, kYellow);

	// fps display
	static float frameTimer = 0.0f;
	static int frames = 0;
	static string fps = " fps";

	frameTimer += mDelta;
	++frames;

	if (frameTimer > 1.0f)
	{
		frameTimer -= 1.0f;

		fps = to_string(frames) + " fps";
		frames = 0;
	}

	mFont->Draw(fps, 0, 0, tle::kWhite);
}

void CPlayState::AnimateHealth(float delta)
{
	//Find the proportion of the bar that should be filled
	float ratio = static_cast<float>(mPlayer1.GetHealth()) / static_cast<float>(mPlayer1.GetMaxHealth());

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
	//Find the proportion of the bar that should be filled
	float ratio = static_cast<float>(mPlayer1.GetShield()) / static_cast<float>(mPlayer1.GetMaxShield());

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

