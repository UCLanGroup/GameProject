#include "CWeapon.h"

CWeapon::CWeapon(tle::IModel* parent, tle::IMesh* mesh, int damage, float projSpeed, float fireRate)
{
	mParent = parent;
	mProjMesh = mesh;
	mDamage = damage;
	mProjSpeed = projSpeed;
	mFireRate = fireRate;
	mTimer = 0.0f;
}

void CWeapon::Update(float delta, BulletList& projectiles)
{
	mTimer += delta;
	while (mTimer > mFireRate)
	{
		float matrix[16];
		mParent->GetMatrix(matrix);

		res_ptr<CProjectile> newBullet = move(CPool<CProjectile>::GetInstance()->GetRes());
		newBullet->SetMatrix(matrix);
		newBullet->SetDamage(mDamage);
		newBullet->SetSpeed(mProjSpeed);

		projectiles.push_back(move(newBullet));

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

IModel* CWeapon::GetParent()
{
	return mParent;
}

IMesh* CWeapon::GetProjMesh()
{
	return mProjMesh;
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

void CWeapon::SetParent(IModel* parent)
{
	mParent = parent;
}

void CWeapon::SetProjMesh(IMesh* projMesh)
{
	mProjMesh = projMesh;
}