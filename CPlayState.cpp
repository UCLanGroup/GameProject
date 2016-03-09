// Last updated: 22.02.16

#include "Globals.h"
#include "CGameStateHandler.h"
#include "CPlayState.h"
#include <iostream>

CPlayState CPlayState::mPlayState;

void CPlayState::Init()
{
	// GRAPHICS
	mFloorMesh = gEngine->LoadMesh(GROUND_MESH);
	mFloor = mFloorMesh->CreateModel(-6.0f, -1000.0f, -5.5f);
	mFloor->SetSkin(METAL_TEX);

	mUI = gEngine->CreateSprite(UI, 0.0f, 0.0f, 0.0f);

	mCam = gEngine->CreateCamera(kManual, 0.0f, 200.0f, 0.0f);
	mCam->RotateLocalX(90.0f);

	// SYSTEM
	mPlayer1.Init();
	playerList.push_back(&mPlayer1);

	// AI
	mEnemyManager.reset(new CEnemyManager("level0.txt"));
	mEnemyManager->SetLists(&playerList, &mPBullets, &mEBullets);
	
	mExplosions = CExplosionPool::Instance();
	mExplosions->Init();

	// SOUND
	if (!mBufferShoot.loadFromFile(SOUND_SHOOT))
	{
		cout << "CPlayState.cpp: Error loading sound file" << endl;
	}

	mSound.setBuffer(mBufferShoot);
	mSound.setVolume(30.0f);
	
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

	// Must be after bullet cleanup. Bullet mesh
	// needs to exist to remove bullet models. 
	// Bullet mesh is owned by player.
	mPlayer1.Cleanup();
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

	if (gEngine->KeyHeld(KEY_FIRE))
	{
		if (mSound.getStatus() == sf::SoundSource::Stopped)
		{
			mSound.play();
		}
		mPlayer1.GetWeapon()->Update(mDelta, mPBullets);
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
		else if (mPlayer1.CollidesSphere(bullet->get())) //Check collision with Player
		{
			mPlayer1.TakeDamage((*bullet)->GetDamage());
			bullet = mEBullets.erase(bullet);
		}
		else
		{
			bullet++;
		}
	}
}

void CPlayState::Draw(CGameStateHandler * game)
{
	// Draw the scene
	gEngine->DrawScene();
}

