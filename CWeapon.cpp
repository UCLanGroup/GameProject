#include "CWeapon.h"
#include <algorithm>

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
}

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
		if (mFireSound.getBuffer() != NULL)
		{
			mFireSound.play();
		}
	}
}

void CWeapon::Upgrade()
{
	if (mMaxLevel > mLevel)
	{
		++mLevel;
	}
}

//Gets

int CWeapon::GetMaxLevel()
{
	return mMaxLevel;
}

int CWeapon::GetLevel()
{
	return mLevel;
}

int CWeapon::GetDamage()
{
	return mDamage;
}

float CWeapon::GetProjSpeed()
{
	return mProjSpeed;
}

float CWeapon::GetFireRate()
{
	return mFireRate;
}

float CWeapon::GetTimer()
{
	return mTimer;
}

bool CWeapon::IsFiring()
{
	return mIsfiring;
}

IEntity* CWeapon::GetParent()
{
	return mpParent;
}

IEntity* CWeapon::GetTarget()
{
	return mpTarget;
}

BulletList* CWeapon::GetBulletList()
{
	return mpProjectiles;
}

//Sets

void CWeapon::SetMaxLevel(int level)
{
	mMaxLevel = level;
}

void CWeapon::SetLevel(int level)
{
	mLevel = level;
}

void CWeapon::SetDamage(int damage)
{
	mDamage = damage;
}

void CWeapon::SetProjSpeed(float projSpeed)
{
	mProjSpeed = projSpeed;
}

void CWeapon::SetFireRate(float fireRate)
{
	mFireRate = fireRate;
}

void CWeapon::SetTimer(float time)
{
	mTimer = time;
}

void CWeapon::SetFiring(bool isFiring)
{
	mIsfiring = isFiring;
}

void CWeapon::SetParent(IEntity* pParent)
{
	mpParent = pParent;
}

void CWeapon::SetTarget(IEntity* pTarget)
{
	mpTarget = pTarget;
}

void CWeapon::SetBulletList(BulletList* pBulletList)
{
	mpProjectiles = pBulletList;
}

void CWeapon::SetFireSound(const sf::SoundBuffer &soundBuffer)
{
	mFireSound.setBuffer(soundBuffer);
}

CWeapon::~CWeapon()
{

}