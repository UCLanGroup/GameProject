#include "CPlayer.h"
#include "CExplosionPool.h"
#include "CBlaster.h"
#include "CShotGun.h"
#include "CMissileLauncher.h"
#include "CChaosGun.h"
#include "CLaser.h"
#include "CMatrix4x4.h"
#include "KeyBinds.h"
#include <algorithm>

//Initial set up
//It is not safe to use other player functions until Init is called
void CPlayer::Init()
{
	//Model
	SetMesh(PLAYER_MESH);
	mModel->SetPosition(0.0f, 0.0f, AREA_BOUNDS_BOTTOM + 10.0f);
	
	for (int i = 1; i <= 10; i++)
	{
		gEngine->Load(PLAYER_MESH, 1, PLAYER_INVUL_TEX + to_string(i) + ".png");
	}

	//Shield
	mShieldMesh = gEngine->LoadMesh(SHIELD_MESH);
	mShieldModel = mShieldMesh->CreateModel(0.0f, 0.0f, 0.0f);
	mShieldModel->Scale(12.0f);
	mShieldModel->AttachToParent(mModel);

	//Weapon
	mMainWeapon.reset(new CBlaster(this, 1, 100.0f, 0.1f));
	mMainWeapon->SetBulletList(mpPlayerBullets);

	//Stats
	mMaxHealth = 100;
	mHealth = 100;
	mMaxShield = 50;
	mShield = 50;
	mSpeed = 50.0f;
	mRotation = 0.0f;

	mLives = 3;
	mScore = 0;

	//Timers
	mRegenTimer = 0.0f;
	mInvulTimer = 0.0f;
	mInvulTextureTimer = 0.0f;
	mWeaponPowerupTimer = 0.0f;

	//Invul
	mInvulTexture = 0;
	mInvulTextureAccending = false;

	SetRadius(5.0f);
	SetDead(false);

	mInitialised = true;
}

//Removes all models and sprites
//It is not safe to use other player functions after Cleanup until Init is called again
void CPlayer::Cleanup()
{
	GetMesh()->RemoveModel(mModel);
	mModel = 0;
	mShieldMesh->RemoveModel(mShieldModel);
	mShieldModel = 0;
	mMainWeapon.reset();

	mInitialised = false;
}

//Moves and updates the player
void CPlayer::Move(float dt)
{
	if (gEngine->KeyHeld(KeyBinds::Up))
	{
		mModel->MoveZ(mSpeed * dt);
		if (mModel->GetZ() > AREA_BOUNDS_TOP)
		{
			mModel->SetZ(AREA_BOUNDS_TOP);
		}
	}
	if (gEngine->KeyHeld(KeyBinds::Down))
	{
		mModel->MoveZ(-mSpeed * dt);
		if (mModel->GetZ() < AREA_BOUNDS_BOTTOM)
		{
			mModel->SetZ(AREA_BOUNDS_BOTTOM);
		}
	}

	bool rotatePlane = true;
	if (!gEngine->KeyHeld(KeyBinds::Left) && !gEngine->KeyHeld(KeyBinds::Right))
	{
		rotatePlane = false;
	}

	// LEVEL PLANE WHEN NOT TURNING
	if (rotatePlane == false)
	{
		if (mRotation > 0.5f)
		{
			float rotAmount = min(kRotateSpeed * dt, mRotation);
			mModel->RotateZ(rotAmount);
			mRotation -= rotAmount;
		}
		else if (mRotation < -0.5f)
		{
			float rotAmount = max(kRotateSpeed * -dt, mRotation);
			mModel->RotateZ(rotAmount);
			mRotation -= rotAmount;
		}
	}

	if (gEngine->KeyHeld(KeyBinds::Left))
	{
		mModel->MoveX(-mSpeed * dt);
		if (mModel->GetX() < AREA_BOUNDS_LEFT)
		{
			mModel->SetX(AREA_BOUNDS_LEFT);
		}

		if (mRotation >= -kMaxLean)
		{
			float rotAmount = kRotateSpeed * dt;
			mModel->RotateZ(rotAmount);
			mRotation -= rotAmount;
		}
	}
	if (gEngine->KeyHeld(KeyBinds::Right))
	{
		mModel->MoveX(mSpeed * dt);
		if (mModel->GetX() > AREA_BOUNDS_RIGHT)
		{
			mModel->SetX(AREA_BOUNDS_RIGHT);
		}

		if (mRotation <= kMaxLean)
		{
			float rotAmount = kRotateSpeed * dt;
			mModel->RotateZ(-rotAmount);
			mRotation += rotAmount;
		}
	}

	//Weapon

	if (gEngine->KeyHeld(KeyBinds::Fire))
	{
		//Fire the weapon
		if (mBonusWeapon)
		{
			mBonusWeapon->SetFiring(true);
			mMainWeapon->SetFiring(false);
		}
		else
		{
			mMainWeapon->SetFiring(true);
		}
	}
	else
	{
		mMainWeapon->SetFiring(false);
		if (mBonusWeapon)
		{
			mBonusWeapon->SetFiring(false);
		}
	}

	mMainWeapon->Update(dt);

	if (mBonusWeapon)
	{
		//Update the bonus weapon if there is one
		mBonusWeapon->Update(dt);
		mWeaponPowerupTimer -= dt;
		
		//Remove the bonus weapon once its duration has ended
		if (mWeaponPowerupTimer < 0.0f)
		{
			mBonusWeapon.reset();
		}
	}

	if (kCheatMode) //If this is false then the contents of the if is optimised away in release mode
	{
		if (gEngine->KeyHit(Key_1)) //Reset player's main weapon by to level 1
		{
			mMainWeapon.reset(new CBlaster(this, 1, 100.0f, 0.1f));
			mMainWeapon->SetBulletList(mpPlayerBullets);
			mWeaponPowerupTimer = 0.0f; //Triggers the bonus weapon to be removed during the next frame
		}
		else if (gEngine->KeyHit(Key_2))
		{
			SetBonusWeapon(new CMissileLauncher(this, 5, 100.0f, 0.2f), 10.0f);
		}
		else if (gEngine->KeyHit(Key_3))
		{
			SetBonusWeapon(new CShotGun(this, 1, 100.0f, 0.33f, 5), 10.0f);
		}
		else if (gEngine->KeyHit(Key_4))
		{
			SetBonusWeapon(new CChaosGun(this, 2, 100.0f, 0.05f), 10.0f);
		}
		else if (gEngine->KeyHit(Key_5))
		{
			SetBonusWeapon(new CLaser(this, 2, 0.1f), 10.0f);
		}
		else if (gEngine->KeyHit(Key_6))
		{
			SetBonusWeapon(new CShotGun(this, 1, 100.0f, 0.33f, 72, 360.0f), 10.0f);
		}
		else if (gEngine->KeyHit(Key_U)) //Upgrade main weapon
		{
			mMainWeapon->Upgrade();
		}
		else if (gEngine->KeyHit(Key_I)) //Toggle player invulnerability
		{
			if (mInvulTimer > 0.0f) //Turn off
			{
				mInvulTimer = 0.00001f;
			}
			else
			{
				MakeInvulnerable(999999.9f);
			}
		}
	}

	//Shield Regen

	if (mShield < mMaxShield)
	{
		mRegenTimer += dt;
		
		while (mRegenTimer > kShieldRegenRate && mShield < mMaxShield)
		{
			if (mShield == 0) //Reattach shield if hidden
			{
				mShieldModel->SetPosition(0.0f, 0.0f, 0.0f);
				mShieldModel->AttachToParent(mModel);
			}
			mShield++;

			mRegenTimer -= kShieldRegenRate;
		}
	}

	//Invulerability

	if (mInvulTimer > 0.0f)
	{
		mInvulTimer -= dt;
		mInvulTextureTimer -= dt;

		if (mInvulTimer < 0.0f)
		{
			tlx::CMatrix4x4 matrix;
			mModel->GetMatrix(matrix.m);

			mShieldModel->DetachFromParent();
			gEngine->CacheModel(mModel, PLAYER_INVUL_TEX + to_string(mInvulTexture) + ".png");

			mModel = gEngine->GetModel(GetMesh());
			mModel->SetMatrix(matrix.m);

			if (mShield > 0)
			{
				mShieldModel->AttachToParent(mModel);
			}
		}
		else if(mInvulTextureTimer < 0.0f)
		{
			tlx::CMatrix4x4 matrix;
			mModel->GetMatrix(matrix.m);

			mShieldModel->DetachFromParent();
			gEngine->CacheModel(mModel, PLAYER_INVUL_TEX + to_string(mInvulTexture) + ".png");

			do {
				mInvulTextureTimer += kInvulTextureRate;
				mInvulTexture += mInvulTextureAccending ? 1 : -1;
			} while (mInvulTextureTimer < 0.0f);
			
			if (mInvulTexture == 1 || mInvulTexture == 10)
			{
				mInvulTextureAccending = !mInvulTextureAccending;
			}

			mModel = gEngine->GetModel(GetMesh(), PLAYER_INVUL_TEX + to_string(mInvulTexture) + ".png");
			mModel->SetMatrix(matrix.m);

			if (mShield > 0)
			{
				mShieldModel->AttachToParent(mModel);
			}
		}
	}
}

//Checks the collision between the player and enemy projectiles
void CPlayer::CheckCollision()
{
	//No collision check atm
	for (auto bullet = mpEnemyBullets->begin(); bullet != mpEnemyBullets->end(); /**/)
	{
		if (CollidesSphere(bullet->get()))
		{
			TakeDamage((*bullet)->GetDamage());
			(*bullet)->SetDead(true);
			bullet = mpEnemyBullets->erase(bullet);
		}
		else
		{
			bullet++;
		}
	}
}

//The player takes damage to the shield or health is there is no shield
//Sets dead flag if it kills the player
void CPlayer::TakeDamage(int damage)
{
	//Don't take damage if invulnerable
	if (mInvulTimer > 0.0f)
	{
		return;
	}

	mRegenTimer = -5.0f; //5 second delay before shield regen starts

	if (mShield > 0)
	{
		if (damage >= mShield) //Shield is destroyed
		{
			//Apply left over damage to health
			mHealth -= damage - mShield;

			//Remove shield model
			mShieldModel->DetachFromParent();
			mShieldModel->SetPosition(OFF_SCREEN_X, OFF_SCREEN_Y, OFF_SCREEN_Z);
		}
		mShield -= min(damage, mShield);
	}
	else
	{
		mHealth -= damage;
	}

	if (mHealth <= 0)
	{
		SetDead(true);
	}
}

//Makes the player invulnerable for a specific duration
void CPlayer::MakeInvulnerable(float time)
{
	if (mInvulTimer > 0)
	{
		//Already invulnerable, just extend the time
		mInvulTimer = time;
		return;
	}
	mInvulTimer = time;
	mInvulTextureTimer = kInvulTextureRate;
	mInvulTexture = 1;
	mInvulTextureAccending = true;

	tlx::CMatrix4x4 matrix;
	mModel->GetMatrix(matrix.m);

	mShieldModel->DetachFromParent();
	gEngine->CacheModel(mModel);

	mModel = gEngine->GetModel(GetMesh(), PLAYER_INVUL_TEX + to_string(mInvulTexture) + ".png");
	mModel->SetMatrix(matrix.m);

	if (mShield > 0)
	{
		mShieldModel->AttachToParent(mModel);
	}
}

//Increases the player's score
//Pass a negative to decrease the score
void CPlayer::IncreaseScore(int value)
{
	mScore += value;
}

//Removes a life from the player and handles death
void CPlayer::LoseLife()
{
	CExplosionPool::Instance()->Spawn(mModel->GetX(), mModel->GetY(), mModel->GetZ(), GetRadius() * 2.0f);

	if (mLives)
	{
		mModel->SetPosition(0.0f, 0.0f, AREA_BOUNDS_BOTTOM + 10.0f);
		mHealth = mMaxHealth;
		mShield = mMaxShield;

		mShieldModel->SetPosition(0.0f, 0.0f, 0.0f);
		mShieldModel->AttachToParent(mModel);
		
		MakeInvulnerable(5.0f);

		mBonusWeapon.reset(); //Ensure there is no bonus weapon
		mMainWeapon->SetLevel(1); //Reset to level to 1

		SetDead(false);
		mLives--;
	}
	else
	{
		mModel->SetPosition(OFF_SCREEN_X, OFF_SCREEN_Y, OFF_SCREEN_Z);
	}
}

//Gives the player and extra life
void CPlayer::GainLife()
{
	if (mLives < kMaxLives)
		++mLives;
}

//Upgrades the main weapon
void CPlayer::UpgradeWeapon()
{
	mMainWeapon->Upgrade();
}

//Sets

//Sets the score
void CPlayer::SetScore(int score)
{
	mScore = score;
}

//Sets the number of extra lives the player has
void CPlayer::SetLives(int lives)
{
	mLives = lives;
}

//Sets the health, this is capped at the player's max health
void CPlayer::SetHealth(int health)
{
	if (mMaxHealth < health)
	{
		mHealth = mMaxHealth;
	}
	else
	{
		mHealth = health;
	}
}

//Sets the maximum health amount
void CPlayer::SetMaxHealth(int health)
{
	mMaxHealth = health;
}

//Sets the shield, this is capped at the player's max shield
void CPlayer::SetShield(int shield)
{
	if (mMaxShield < shield)
	{
		mShield = mMaxShield;
	}
	else
	{
		mShield = shield;
	}
}

//Sets the maximum shield amount
void CPlayer::SetMaxShield(int shield)
{
	mMaxShield = shield;
}

//Sets the main weapon that the player uses at all times
void CPlayer::SetMainWeapon(CWeapon* weapon)
{
	mMainWeapon.reset(weapon);
	mMainWeapon->SetBulletList(mpPlayerBullets);
}

//Sets the bonus weapon of the player, the bonus weapon lasts for a set duration
//While active the bonus weapon will be used instead of the main weapon
void CPlayer::SetBonusWeapon(CWeapon* weapon, float duration)
{
	mBonusWeapon.reset(weapon);
	mBonusWeapon->SetParent(this);
	mBonusWeapon->SetBulletList(mpPlayerBullets);
	mWeaponPowerupTimer = duration;
}

//Gives the player access to the player and enemy bullet lists
void CPlayer::SetLists(BulletList* playerBullets, BulletList* enemyBullets)
{
	mpPlayerBullets = playerBullets;
	mpEnemyBullets = enemyBullets;

	if (mMainWeapon.get()) mMainWeapon->SetBulletList(playerBullets);
}

//Gets

//Returns the player's score
int CPlayer::GetScore()
{
	return mScore;
}

//Returns the number of extra lives remaining
int CPlayer::GetLives()
{
	return mLives;
}

//Returns the current health
int CPlayer::GetHealth()
{
	return mHealth;
}

//Returns the maximum amount of health
int CPlayer::GetMaxHealth()
{
	return mMaxHealth;
}

//Returns the current shield
int CPlayer::GetShield()
{
	return mShield;
}

//Returns the maximum amount of shield
int CPlayer::GetMaxShield()
{
	return mMaxShield;
}

//Returns a pointer to the main weapon
CWeapon* CPlayer::GetMainWeapon()
{
	return mMainWeapon.get();
}

//Inherited from IEntity
void CPlayer::Reset()
{
	mHealth = 100;
	mMaxHealth = 100;
	mShield = 50;
	mMaxShield = 50;
	mRegenTimer = 0.0f;
}

//Ensures all player models are destroyed (calls Cleanup())
CPlayer::~CPlayer()
{
	if (mInitialised)
	{
		Cleanup();
	}
}
