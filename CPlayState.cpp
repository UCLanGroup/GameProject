// Last updated: 22.02.16

#include "Globals.h"
#include "CGameStateHandler.h"
#include "CPlayState.h"
#include <iostream>
#include <sstream>

CPlayState CPlayState::mPlayState;

void CPlayState::Init()
{
	// GRAPHICS
	mFloorMesh = gEngine->LoadMesh(GROUND_MESH);
	mFloor = mFloorMesh->CreateModel(-6.0f, -1000.0f, -5.5f);
	mFloor->SetSkin(METAL_TEX);

	mUI = gEngine->CreateSprite(UI, 0.0f, 0.0f, 0.2f);
	mUI2 = gEngine->CreateSprite(UI2, 0.0f, 0.0f, 0.1f);

	mCam = gEngine->CreateCamera(kManual, 0.0f, 200.0f, 0.0f);
	mCam->RotateLocalX(90.0f);

	// SYSTEM
	mPlayer1.Init();
	mPlayer1.SetLists(&mPBullets, &mEBullets);
	mPlayerList.push_back(&mPlayer1);

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
}

void CPlayState::Draw(CGameStateHandler * game)
{
	// Draw the scene
	gEngine->DrawScene();
}

