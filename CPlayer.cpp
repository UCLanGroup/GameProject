#include "CPlayer.h"
#include "CMeshCache.h"
#include <algorithm> //for min & max functions

void CPlayer::Init()
{
	//Model
	mMesh = gEngine->LoadMesh(PLAYERMESH);
	model = mMesh->CreateModel(0.0f, 0.0f, 0.0f);

	//Shield
	mShieldMesh = gEngine->LoadMesh(SHIELD_MESH);
	mShieldModel = mShieldMesh->CreateModel(0.0f, 0.0f, 0.0f);
	mShieldModel->Scale(12.0f);
	mShieldModel->AttachToParent(model);

	//Weapon
	IMesh* bulletMesh = gEngine->LoadMesh(BULLET_MESH);
	mWeapon.reset(new CWeapon(model, bulletMesh, 1, 100.0f, 0.1f));

	//Stats
	mHealth = 100;
	mMaxHealth = 100;
	mShield = 50;
	mMaxShield = 50;
	mShieldRegenRate = 0.25f;
	mRegenTimer = 0.0f;
	mSpeed = 50.0f;
	mRadius = 5.0f;
}

void CPlayer::Move(float dt)
{
	if (gEngine->KeyHeld(KEY_UP))
	{
		model->MoveZ(mSpeed * dt);
		if (model->GetZ() > AREA_BOUNDS_TOP)
		{
			model->SetZ(AREA_BOUNDS_TOP);
		}
	}
	if (gEngine->KeyHeld(KEY_DOWN))
	{
		model->MoveZ(-mSpeed * dt);
		if (model->GetZ() < AREA_BOUNDS_BOTTOM)
		{
			model->SetZ(AREA_BOUNDS_BOTTOM);
		}
	}
	if (gEngine->KeyHeld(KEY_LEFT))
	{
		model->MoveX(-mSpeed * dt);
		if (model->GetX() < AREA_BOUNDS_LEFT)
		{
			model->SetX(AREA_BOUNDS_LEFT);
		}
	}
	if (gEngine->KeyHeld(KEY_RIGHT))
	{
		model->MoveX(mSpeed * dt);
		if (model->GetX() > AREA_BOUNDS_RIGHT)
		{
			model->SetX(AREA_BOUNDS_RIGHT);
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
				mShieldModel->AttachToParent(model);
			}
			mShield++;

			mRegenTimer -= mShieldRegenRate;
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

//Inherited from ICollidable
Vector3 CPlayer::GetCenterPoint()
{
	return Vector3(model->GetX(), model->GetY(), model->GetZ());
}

bool CPlayer::GetMeshAndMatrix(IMesh* mesh, float* matrix)
{
	//Check if mesh and model exists
	if (mMesh == 0 || model == 0)
	{
		return false;
	}

	mesh = mMesh;
	model->GetMatrix(matrix); //Fills in the matrix

	return true;
}

CPlayer::~CPlayer()
{
	//mesh->RemoveModel(model);
	//gEngine->RemoveMesh(mesh);
}
