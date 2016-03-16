#include "CPlayer.h"
#include <algorithm> //for min & max functions
#include <iostream>

void CPlayer::Init()
{
	//Model
	SetMesh(PLAYER_MESH);

	//Shield
	mShieldMesh = gEngine->LoadMesh(SHIELD_MESH);
	mShieldModel = mShieldMesh->CreateModel(0.0f, 0.0f, 0.0f);
	mShieldModel->Scale(12.0f);
	mShieldModel->AttachToParent(mModel);

	//Weapon
	mProjectileMesh = gEngine->LoadMesh(BULLET_MESH);
	mWeapon.reset(new CWeapon(mModel, mProjectileMesh, 1, 100.0f, 0.1f));

	//Stats
	mHealth = 100;
	mMaxHealth = 100;
	mShield = 50;
	mMaxShield = 50;
	mShieldRegenRate = 0.25f;
	mRegenTimer = 0.0f;
	mSpeed = 50.0f;
	SetRadius(5.0f);
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
	float rotateSpeed = 400.0f;
	if (!gEngine->KeyHeld(KEY_LEFT) && !gEngine->KeyHeld(KEY_RIGHT))
	{
		rotatePlane = false;
	}

	// LEVEL PLANE WHEN NOT TURNING
	if (rotatePlane == false)
	{
		float rotAmount = rotateSpeed * dt;

		if (mRotation > 0.4f)
		{
			mModel->RotateZ(rotAmount);
			mRotation -= rotAmount;
		}
		else if (mRotation < 0.4f)
		{
			mModel->RotateZ(-rotAmount);
			mRotation += rotAmount;
		}
	}

	if (gEngine->KeyHeld(KEY_LEFT))
	{
		mModel->MoveX(-mSpeed * dt);
		if (mModel->GetX() < AREA_BOUNDS_LEFT)
		{
			mModel->SetX(AREA_BOUNDS_LEFT);
		}

		if (mRotation >= -50.0f)
		{
			float rotAmount = rotateSpeed * dt;
			mModel->RotateZ(rotAmount);
			mRotation -= rotAmount;
			cout << mRotation << endl;
		}
	}
	if (gEngine->KeyHeld(KEY_RIGHT))
	{
		mModel->MoveX(mSpeed * dt);
		if (mModel->GetX() > AREA_BOUNDS_RIGHT)
		{
			mModel->SetX(AREA_BOUNDS_RIGHT);
		}

		if (mRotation <= 70.0f)
		{
			float rotAmount = rotateSpeed * dt;
			mModel->RotateZ(-rotAmount);
			mRotation += rotAmount;
			cout << mRotation << endl;
		}
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
}

void CPlayer::TakeDamage(int damage)
{
	mRegenTimer = -5.0f; //5 second delay before shield regen starts

	if (mShield > 0)
	{
		if (damage >= mShield) //Shield is destroyed
		{
			//Apply left over damage to health
			mHealth -= mShield - damage;

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
}

//Sets

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

//Gets

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
