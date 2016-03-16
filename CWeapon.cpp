#include "CWeapon.h"
#include <algorithm>

CWeapon::CWeapon(IEntity* parent, tle::IMesh* mesh, int damage, float projSpeed, float fireRate)
{
	mpParent = parent;
	mpProjMesh = mesh;
	mDamage = damage;
	mProjSpeed = projSpeed;
	mFireRate = fireRate;
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
		float matrix[16];
		mpParent->GetMatrix(matrix);

		res_ptr<CProjectile> newBullet = move(CPool<CProjectile>::GetInstance()->GetRes());
		newBullet->SetMatrix(matrix);
		newBullet->SetDamage(mDamage);
		newBullet->SetSpeed(mProjSpeed);
		newBullet->SetParent(mpParent);

		mpProjectiles->push_back(move(newBullet));

		mTimer -= mFireRate;
	}
}

//Gets

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

IMesh* CWeapon::GetProjMesh()
{
	return mpProjMesh;
}

BulletList* CWeapon::GetBulletList()
{
	return mpProjectiles;
}

//Sets

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

void CWeapon::SetProjMesh(IMesh* pProjMesh)
{
	mpProjMesh = pProjMesh;
}

void CWeapon::SetBulletList(BulletList* pBulletList)
{
	mpProjectiles = pBulletList;
}