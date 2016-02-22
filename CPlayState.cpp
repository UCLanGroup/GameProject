// Last updated: 04.02.16

#include "Globals.h"
#include "CGameStateHandler.h"
#include "CPlayState.h"

CPlayState CPlayState::mPlayState;

void CPlayState::Init()
{
	mFloorMesh = gEngine->LoadMesh(GROUND_MESH);
	mFloor = mFloorMesh->CreateModel(-6.0f, -10.0f, -5.5f);

	mUI = gEngine->CreateSprite(UI, 0.0f, 0.0f, 0.0f);

	mCam = gEngine->CreateCamera(kManual, 0.0f, 200.0f, 0.0f);
	mCam->RotateLocalX(90.0f);

	mPlayer1.Init();
	mPlayer1.model->Scale(1.0f);

	mEnemyManager.reset(new CEnemyManager("level0.txt"));
	
	mExplosions = CExplosionPool::Instance();
	mExplosions->Init();

	float x = mPlayer1.model->GetX();
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
		mPlayer1.GetWeapon()->Update(mDelta, mPBullets);
	}

	mEnemyManager->Update(mDelta);

	mExplosions->Update(mDelta);

	//Update all player projectiles
	for (auto bullet = mPBullets.begin(); bullet != mPBullets.end(); )
	{
		(*bullet)->Update(mDelta);

		auto enemy = mEnemyManager->GetEnemies().begin();
		auto enemyEnd = mEnemyManager->GetEnemies().end();

		bool hit = false;

		//Some collision detection - This will be changed tomorrow
		while (enemy != enemyEnd && !hit)
		{
			if ((*enemy)->CollidesSphere(bullet->get()) && (*enemy)->GetHealth() > 0) //Only collide if a previous bullet hasn't killed the enemy
			{
				(*enemy)->TakeDamage((*bullet)->GetDamage());
				hit = true;
			}
			enemy++;
		}
		
		if (hit)
		{
			mExplosions->Spawn((*bullet)->GetCenterPoint().GetX(), 0.0f, (*bullet)->GetCenterPoint().GetZ(), (*bullet)->GetBoundingRadius());
			bullet = mPBullets.erase(bullet);
		}
		else if ((*bullet)->IsOutOfBounds())
		{
			bullet = mPBullets.erase(bullet);
		}
		else
		{
			//Incremenet if current bullet was not removed
			bullet++;
		}
	}

	//Update all enemy projectiles
	for (auto bullet = mEBullets.begin(); bullet != mEBullets.end(); bullet++)
	{
		(*bullet)->Update(mDelta);

		//Check collision with Player
		mPlayer1.CollidesSphere(bullet->get() );
	}
}

void CPlayState::Draw(CGameStateHandler * game)
{
	// Draw the scene
	gEngine->DrawScene();
}

