#include "CPlayer.h"
#include "CExplosionPool.h"
#include "CBlaster.h"
#include "CShotGun.h"
#include "CMissileLauncher.h"

void CPlayer::Init()
{
	//Model
	SetMesh(PLAYER_MESH);
	mModel->SetPosition(0.0f, 0.0f, AREA_BOUNDS_BOTTOM + 10.0f);

	//Shield
	mShieldMesh = gEngine->LoadMesh(SHIELD_MESH);
	mShieldModel = mShieldMesh->CreateModel(0.0f, 0.0f, 0.0f);
	mShieldModel->Scale(12.0f);
	mShieldModel->AttachToParent(mModel);

	//Weapon
	mProjectileMesh = gEngine->LoadMesh(BULLET_MESH);
	mWeapon.reset(new CBlaster(this, 1, 100.0f, 0.1f));
	mWeapon->SetBulletList(mpPlayerBullets);

	//Stats
	mHealth = 100;
	mScore = 0;
	mLives = 3;
	mMaxHealth = 100;
	mShield = 50;
	mMaxShield = 50;
	mShieldRegenRate = 0.25f;
	mRegenTimer = 0.0f;
	mSpeed = 50.0f;
	mScore = 0;
	SetRadius(5.0f);
	SetDead(false);
}

void CPlayer::Cleanup()
{
	GetMesh()->RemoveModel(mModel);
	mModel = 0;
	mShieldMesh->RemoveModel(mShieldModel);
	mShieldModel = 0;
}

void CPlayer::Move(float dt)
{
	if (gEngine->KeyHeld(KEY_UP))
	{
		mModel->MoveZ(mSpeed * dt);
		if (mModel->GetZ() > AREA_BOUNDS_TOP)
		{
			mModel->SetZ(AREA_BOUNDS_TOP);
		}
	}
	if (gEngine->KeyHeld(KEY_DOWN))
	{
		mModel->MoveZ(-mSpeed * dt);
		if (mModel->GetZ() < AREA_BOUNDS_BOTTOM)
		{
			mModel->SetZ(AREA_BOUNDS_BOTTOM);
		}
	}

	bool rotatePlane = true;
	if (!gEngine->KeyHeld(KEY_LEFT) && !gEngine->KeyHeld(KEY_RIGHT))
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

	if (gEngine->KeyHeld(KEY_LEFT))
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
	if (gEngine->KeyHeld(KEY_RIGHT))
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

	if (gEngine->KeyHeld(KEY_FIRE))
	{
		mWeapon->SetFiring(true);
	}
	else
	{
		mWeapon->SetFiring(false);
	}
	mWeapon->Update(dt);

	if (gEngine->KeyHit(Key_Q))
	{
		mWeapon.reset(new CBlaster(this, 1, 100.0f, 0.1f));
		mWeapon->SetBulletList(mpPlayerBullets);
	}
	else if (gEngine->KeyHit(Key_W))
	{
		mWeapon.reset(new CMissileLauncher(this, 5, 100.0f, 0.2f));
		mWeapon->SetBulletList(mpPlayerBullets);
	}
	else if (gEngine->KeyHit(Key_E))
	{
		mWeapon.reset(new CShotGun(this, 1, 100.0f, 0.33f));
		mWeapon->SetBulletList(mpPlayerBullets);
	}

	//Shield Regen

	if (mShield < mMaxShield)
	{
		mRegenTimer += dt;
		
		while (mRegenTimer > mShieldRegenRate && mShield < mMaxShield)
		{
			if (mShield == 0) //Reattach shield if hidden
			{
				mShieldModel->SetPosition(0.0f, 0.0f, 0.0f);
				mShieldModel->AttachToParent(mModel);
			}
			mShield++;

			mRegenTimer -= mShieldRegenRate;
		}
	}
}

void CPlayer::CheckCollision()
{
	//No collision check atm
	for (auto bullet = mpEnemyBullets->begin(); bullet != mpEnemyBullets->end(); /**/)
	{
		if (CollidesSphere(bullet->get()))
		{
			TakeDamage((*bullet)->GetDamage());
			CVector3 pos = (*bullet)->GetCenterPoint();
			CExplosionPool::Instance()->Spawn(pos.x, pos.y, pos.z, (*bullet)->GetRadius());
			bullet = mpEnemyBullets->erase(bullet);
		}
		else
		{
			bullet++;
		}
	}
}

void CPlayer::TakeDamage(int damage)
{
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

		SetDead(false);
		mLives--;
	}
	else
	{
		mModel->SetPosition(OFF_SCREEN_X, OFF_SCREEN_Y, OFF_SCREEN_Z);
	}
}

void CPlayer::GainLife()
{
	mLives++;
}

void CPlayer::IncreaseScore(int value)
{
	mScore += value;
}

//Sets

void CPlayer::SetScore(int score)
{
	mScore = score;
}

void CPlayer::SetLives(int lives)
{
	mLives = lives;
}

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

void CPlayer::SetMaxHealth(int health)
{
	mMaxHealth = health;
}

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

void CPlayer::SetMaxShield(int shield)
{
	mMaxShield = shield;
}

void CPlayer::SetShieldRegen(float regen)
{
	mShieldRegenRate = regen;
}

void CPlayer::SetLists(BulletList* playerBullets, BulletList* enemyBullets)
{
	mpPlayerBullets = playerBullets;
	mpEnemyBullets = enemyBullets;

	if (mWeapon.get()) mWeapon->SetBulletList(playerBullets);
}

//Gets

int CPlayer::GetScore()
{
	return mScore;
}

int CPlayer::GetLives()
{
	return mLives;
}

int CPlayer::GetHealth()
{
	return mHealth;
}

int CPlayer::GetMaxHealth()
{
	return mMaxHealth;
}

int CPlayer::GetShield()
{
	return mShield;
}

int CPlayer::GetMaxShield()
{
	return mMaxShield;
}

CWeapon* CPlayer::GetWeapon()
{
	return mWeapon.get();
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

CPlayer::~CPlayer()
{
}
