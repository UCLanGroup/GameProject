#include "CPlayer.h"
#include "CExplosionPool.h"
#include "CBlaster.h"
#include "CShotGun.h"
#include "CMissileLauncher.h"
#include "CChaosGun.h"
#include "CLaser.h"
#include "CMatrix4x4.h"

void CPlayer::Init()
{
	//Model
	SetMesh(PLAYER_MESH);
	mModel->SetPosition(0.0f, 0.0f, AREA_BOUNDS_BOTTOM + 10.0f);
	
	for (int i = 1; i <= 10; i++)
	{
		gEngine->Preload(PLAYER_MESH, 1, PLAYER_INVUL_TEX + to_string(i) + ".png");
	}

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
	mInvulTexture = 0;
	mShieldRegenRate = 0.25f;
	mRegenTimer = 0.0f;
	mInvulTimer = 0.0f;
	mInvulTextureTimer = 0.0f;
	mSpeed = 50.0f;
	mScore = 0;
	mInvulTextureAccending = false;
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

	if (gEngine->KeyHit(Key_1))
	{
		mWeapon.reset(new CBlaster(this, 1, 100.0f, 0.1f));
		mWeapon->SetBulletList(mpPlayerBullets);
	}
	else if (gEngine->KeyHit(Key_2))
	{
		mWeapon.reset(new CMissileLauncher(this, 5, 100.0f, 0.2f));
		mWeapon->SetBulletList(mpPlayerBullets);
	}
	else if (gEngine->KeyHit(Key_3))
	{
		mWeapon.reset(new CShotGun(this, 1, 100.0f, 0.33f, 5));
		mWeapon->SetBulletList(mpPlayerBullets);
	}
	else if (gEngine->KeyHit(Key_4))
	{
		mWeapon.reset(new CChaosGun(this, 2, 100.0f, 0.05f));
		mWeapon->SetBulletList(mpPlayerBullets);
	}
	else if (gEngine->KeyHit(Key_5))
	{
		mWeapon.reset(new CLaser(this, 2, 0.1f));
		mWeapon->SetBulletList(mpPlayerBullets);
	}
	else if (gEngine->KeyHit(Key_U))
	{
		mWeapon->Upgrade();
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
