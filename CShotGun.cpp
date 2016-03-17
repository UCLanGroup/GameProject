#define _USE_MATH_DEFINES
#include "CShotGun.h"
#include "CProjectile.h"
#include "CMatrix4x4.h"

CShotGun::CShotGun(IEntity* parent, int damage, float projSpeed, float fireRate, int bulletsPerShot) : CWeapon(parent)
{
	SetDamage(damage);
	SetProjSpeed(projSpeed);
	SetFireRate(fireRate);
	SetTarget(0);
	mBulletsPerShot = max(bulletsPerShot, 3); //Ensures there is at least 3
}

void CShotGun::Fire()
{

	tlx::CMatrix4x4 matrix;
	GetParent()->GetMatrix(matrix.m);

	tlx::CMatrix4x4 rot;
	rot.SetRotationY(30.0f / (180.0f / static_cast<float>(M_PI)));

	matrix *= rot;

	rot.SetRotationY((-60.0f / static_cast<float>(mBulletsPerShot - 1)) / (180.0f / static_cast<float>(M_PI)));

	CProjectile* bullet = 0;

	for (int i = 0; i < mBulletsPerShot;  i++)
	{
		bullet = new CProjectile();
		bullet->SetMatrix(matrix.m);
		matrix *= rot;

		bullet->SetDamage(GetDamage());
		bullet->SetSpeed(GetProjSpeed());
		bullet->SetParent(GetParent());

		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));
	}
}