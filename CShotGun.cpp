#define _USE_MATH_DEFINES
#include "CShotGun.h"
#include "CProjectile.h"
#include "CMatrix4x4.h"
#include <algorithm>

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
	float additionRotation = 30.0f;
	float rotationDelta = (-60.0f / static_cast<float>(mBulletsPerShot - 1));

	CProjectile* bullet = 0;

	for (int i = 0; i < mBulletsPerShot;  i++)
	{
		//Create a bullet with the current matrix
		bullet = CreateProjectile<CProjectile>();

		bullet->GetModel()->RotateY(additionRotation);

		//Update the rotation
		additionRotation += rotationDelta;

		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));
	}
}