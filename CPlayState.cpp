// Last updated: 04.02.16

#include "Globals.h"
#include "CGameStateHandler.h"
#include "CPlayState.h"

CPlayState CPlayState::mPlayState;

void CPlayState::Init()
{
	mFloorMesh = gEngine->LoadMesh(GROUNDMESH);
	mFloor = mFloorMesh->CreateModel(-6.0f, -10.0f, -5.5f);

	mUI = gEngine->CreateSprite(UI, 0.0f, 0.0f, 0.0f);

	mCam = gEngine->CreateCamera(kManual, 0.0f, 200.0f, 0.0f);
	mCam->RotateLocalX(90.0f);

	mPlayer1.Init();

	mEnemyManager.reset(new CEnemyManager("level0.txt"));
	
	mExplosions = CExplosionPool::Instance();
	mExplosions->Init();
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
			if ((*enemy)->CollidesSphere(bullet->get()))
			{
				(*enemy)->TakeDamage((*bullet)->GetDamage());
				if ((*enemy)->GetHealth() <= 0) //If killed by the bullet
				{
					Vector3 loc = (*enemy)->GetCenterPoint();
					mExplosions->Spawn(loc.GetX(), loc.GetY(), loc.GetZ(), (*enemy)->GetRadius());
					mEnemyManager->GetEnemies().erase(enemy);
				}
				hit = true;
				//No need to iterate if bullet hit since it breaks out of the loop
			}
			else
			{
				enemy++;
			}
		}
		
		if (hit)
		{
			mExplosions->Spawn((*bullet)->GetCenterPoint().GetX(), 0.0f, (*bullet)->GetCenterPoint().GetZ(), (*bullet)->GetRadius());
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
	for (auto bullet = mEBullets.begin(); bullet != mEBullets.end(); )
	{
		(*bullet)->Update(mDelta);

		//Check collision with Player
		if (mPlayer1.CollidesSphere(bullet->get()))
		{
			mPlayer1.TakeDamage((*bullet)->GetDamage());
			bullet = mEBullets.erase(bullet);
		}
		else
		{
			bullet++;
		}
	}

	//Collision between the enemies themselves and the player
	for (auto enemy = mEnemyManager->GetEnemies().begin(); enemy != mEnemyManager->GetEnemies().end(); /*NO*/ )
	{
		if (mPlayer1.CollidesSphere((*enemy).get()))
		{
			//Do a lot of damage on collision
			mPlayer1.TakeDamage(50); 
			(*enemy)->TakeDamage(50);
		}
		/*if (mPlayer2.CollidesSphere((*enemy).get()))
		{
			mPlayer2.TakeDamage(50);
			(*enemy)->TakeDamage(50);
		}*/

		if ((*enemy)->GetHealth() <= 0) //If killed by the collision
		{
			Vector3 loc = (*enemy)->GetCenterPoint();
			mExplosions->Spawn(loc.GetX(), loc.GetY(), loc.GetZ(), (*enemy)->GetRadius());
			enemy = mEnemyManager->GetEnemies().erase(enemy);
		}
		else
		{
			enemy++;
		}
	}
}

void CPlayState::Draw(CGameStateHandler * game)
{
	// Draw the scene
	gEngine->DrawScene();
}

