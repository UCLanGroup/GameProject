// Last updated: 22.02.16

#include "Globals.h"
#include "CGameStateHandler.h"
#include "CPlayState.h"
#include <iostream>
#include <sstream>

CPlayState CPlayState::mPlayState;

void CPlayState::Init()
{
	// SYSTEM
	mPlayer1.Init();
	mPlayer1.SetLists(&mPBullets, &mEBullets);
	mPlayerList.push_back(&mPlayer1);

	// GRAPHICS
	mFloorMesh = gEngine->LoadMesh(GROUND_MESH);
	mFloor = mFloorMesh->CreateModel(-6.0f, -1000.0f, -5.5f);
	mFloor->SetSkin(METAL_TEX);

	mUI = gEngine->CreateSprite(UI, 0.0f, 0.0f, 0.2f);
	mUI2 = gEngine->CreateSprite(UI2, 0.0f, 0.0f, 0.1f);

	mCam = gEngine->CreateCamera(kManual, 0.0f, 200.0f, 0.0f);
	mCam->RotateLocalX(90.0f);

	mpHealthBar = gEngine->CreateSprite("healthbar.png", mStartBarPosX, mStartBarPosY, 0.15f);
	mpShieldBar = gEngine->CreateSprite("shieldbar.png", mStartBarPosX, mStartBarPosY + 37.0f, 0.15f);

	// Draw life sprites
	for (int i = 0; i < mPlayer1.GetLives(); i++)
	{
		int startPosX = 505;
		int startPosY = 932;
		int startPosInc = 35;
		ISprite* temp = gEngine->CreateSprite("life.png", startPosX + startPosInc * i, startPosY, 0.01f);
		mLifeSprites.push_back(temp);
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

	gEngine->Preload(HAVOC_BOSS_MESH);
	gEngine->Preload(MISSILE_MESH);

	for (int i = 1; i <= 10; ++i)
	{
		//Preload 200 of each of the smoke particles
		gEngine->Preload(PARTICLE_MODEL, 200, "Smoke" + to_string(i) + ".png");
	}

	// SOUND
	if (!mBufferShoot.loadFromFile(SOUND_SHOOT))
	{
		cout << "CPlayState.cpp: Error loading sound file" << endl;
	}

	mSound.setBuffer(mBufferShoot);
	mSound.setVolume(30.0f);
	
	//Reset timer after finished loading assets
	gEngine->Timer();
}

void CPlayState::Cleanup()
{
	gEngine->RemoveSprite(mUI);
	gEngine->RemoveCamera(mCam);
	mFloorMesh->RemoveModel(mFloor);
	gEngine->RemoveMesh(mFloorMesh);
	mPBullets.clear();
	mEBullets.clear();
	mEnemyManager.reset();
	mExplosions->CleanUp();

	gEngine->RemoveFont(mFont);
	for (int i = 0; i < mLifeSprites.size(); i++)
	{
		gEngine->RemoveSprite(mLifeSprites[i]);
	}
	mLifeSprites.clear();
	gEngine->RemoveSprite(mpHealthBar);
	gEngine->RemoveSprite(mpShieldBar);

	// Must be after bullet cleanup. Bullet mesh
	// needs to exist to remove bullet models. 
	// Bullet mesh is owned by player.
	mPlayer1.Cleanup();

	//Clear player list
	mPlayerList.clear();

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

	mPlayer1.Move(mDelta);
	mPlayer1.CheckCollision();

	if (gEngine->KeyHeld(KEY_FIRE))
	{
		if (mSound.getStatus() == sf::SoundSource::Stopped)
		{
			mSound.play();
		}
	}

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

	if(mPlayer1.IsDead())
	{
		mPlayer1.LoseLife();

		//If the player has another life then start the new life

		if (mLifeSprites.size() > 0)
		{
			gEngine->RemoveSprite(mLifeSprites.back());
			mLifeSprites.pop_back();

			mpHealthBar->SetX(mStartBarPosX);
			mpShieldBar->SetX(mStartBarPosX);
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
}

void CPlayState::AnimateHealth(float delta)
{
	//Find the proportion of the bar that should be filled
	float ratio = static_cast<float>(mPlayer1.GetHealth()) / static_cast<float>(mPlayer1.GetMaxHealth());

	//Find the x position the bar needs to be
	float target = static_cast<float>(mStartBarPosX) - mBarSize + ratio * mBarSize;

	//Move the bar towards the required position
	if (target > mpHealthBar->GetX())
	{
		float newLoc = min(target, mpHealthBar->GetX() + (delta * mBarSpeed));
		mpHealthBar->SetX(newLoc);
	}
	else
	{
		float newLoc = max(target, mpHealthBar->GetX() - (delta * mBarSpeed));
		mpHealthBar->SetX(newLoc);
	}
}

void CPlayState::AnimateShield(float delta)
{
	//Find the proportion of the bar that should be filled
	float ratio = static_cast<float>(mPlayer1.GetShield()) / static_cast<float>(mPlayer1.GetMaxShield());

	//Find the x position the bar needs to be
	float target = static_cast<float>(mStartBarPosX) - mBarSize + ratio * mBarSize;

	//Move the bar towards the required position
	if (target > mpShieldBar->GetX())
	{
		float newLoc = min(target, mpShieldBar->GetX() + (delta * mBarSpeed));
		mpShieldBar->SetX(newLoc);
	}
	else
	{
		float newLoc = max(target, mpShieldBar->GetX() - (delta * mBarSpeed));
		mpShieldBar->SetX(newLoc);
	}
}

void CPlayState::Draw(CGameStateHandler * game)
{
	// Draw the scene
	gEngine->DrawScene();
}

