#include "CWeapon.h"
#include <algorithm>

//Creates a weapon
CWeapon::CWeapon(IEntity* parent)
{
	mpParent = parent;
	mMaxLevel = 1;
	mLevel = 1;
	mDamage = 1;
	mProjSpeed = 100.0f;
	mFireRate = 1.0f;
	mTimer = 0.0f;
	mpProjectiles = 0;
	mIsfiring = false;
	mRotation = 0.0f;
	mOffset = {0.0f, 0.0f, 0.0f};
	mFireSound = 0;
}

//Updates the by reloading and/or firing
void CWeapon::Update(float delta)
{
	mTimer += delta;

	if (!mIsfiring)
	{
		//Cap timer at reloaded position
		mTimer = min(mTimer, mFireRate);
		return; //Avoid firing
	}

	while (mTimer > mFireRate)
	{
		Fire();
		mTimer -= mFireRate;

		//Play the fire sound
		if (mFireSound)
		{
			mFireSound->Play();
		}
	}
}

//Increases the weapon's level if not already at the maximum level
void CWeapon::Upgrade()
{
	if (mMaxLevel > mLevel)
	{
		++mLevel;
	}
}

//Gets

//Gets the weapon's maximum level
int CWeapon::GetMaxLevel()
{
	return mMaxLevel;
}

//Gets the weapon's current level
int CWeapon::GetLevel()
{
	return mLevel;
}

//Gets the weapon's damage
int CWeapon::GetDamage()
{
	return mDamage;
}

//Gets the weapon's projectile speed
float CWeapon::GetProjSpeed()
{
	return mProjSpeed;
}

//Gets the rotational offset
float CWeapon::GetRotation()
{
	return mRotation;
}

//Gets the weapon's fire rate
float CWeapon::GetFireRate()
{
	return mFireRate;
}

//Returns whether the weapon is firing or not
bool CWeapon::IsFiring()
{
	return mIsfiring;
}

//Gets the positional offset from the weapon's parent
CVector3& CWeapon::GetPosOffset()
{
	return mOffset;
}

//Gets the entity that the weapon is equiped to
IEntity* CWeapon::GetParent()
{
	return mpParent;
}

//Gets the entity that the weapon is targetting
//If there is no target then zero is returned
IEntity* CWeapon::GetTarget()
{
	return mpTarget;
}

//Gets the bullet list that projectiles created by the weapon are added to
BulletList* CWeapon::GetBulletList()
{
	return mpProjectiles;
}

//Gets the sound that is played when the weapon fires
//If the weapon has no sound then zero is returned
ISound* CWeapon::GetFireSound()
{
	return mFireSound;
}

//Sets

//Sets the weapon's maximum level
void CWeapon::SetMaxLevel(int level)
{
	mMaxLevel = level;
}

//Sets the weapon's current level, this is capped at the weapon's max level
void CWeapon::SetLevel(int level)
{
	mLevel = (level < mMaxLevel ? level : mMaxLevel);
}

//Sets the damage
void CWeapon::SetDamage(int damage)
{
	mDamage = damage;
}

//Sets the projectile of created projectiles
void CWeapon::SetProjSpeed(float projSpeed)
{
	mProjSpeed = projSpeed;
}

//Set the rotational offset
void CWeapon::SetRotation(float rotation)
{
	mRotation = rotation;
}

//Sets the reload time between shots
void CWeapon::SetFireRate(float fireRate)
{
	mFireRate = fireRate;
}

//Sets whether the weapon is firing
void CWeapon::SetFiring(bool isFiring)
{
	mIsfiring = isFiring;
}

//Sets the positional offset from the parent
void CWeapon::SetPosOffset(const CVector3& pos)
{
	mOffset = pos;
}

//Sets the weapon's parent
void CWeapon::SetParent(IEntity* pParent)
{
	mpParent = pParent;
}

//Sets the target that the weapon will fire at
//If no target then the weapon will fire forward
void CWeapon::SetTarget(IEntity* pTarget)
{
	mpTarget = pTarget;
}

//Sets the projectile list that projectiles created by the weapon are added to
void CWeapon::SetBulletList(BulletList* pBulletList)
{
	mpProjectiles = pBulletList;
}

//Sets the sound that is played when the weapon fires
void CWeapon::SetFireSound(ISound* fireSound)
{
	mFireSound = fireSound;
}

//Nick Cage mode
void CWeapon::ActivateTheCage()
{
	mNickMode = true;
}

//Destroys stuff
CWeapon::~CWeapon()
{
	if (mFireSound) gEngine->RemoveSound(mFireSound);
}