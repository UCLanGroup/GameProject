#define _USE_MATH_DEFINES
#include "CShotGun.h"
#include "CProjectile.h"
#include "CMatrix4x4.h"
#include <algorithm>

CShotGun::CShotGun(IEntity* parent, int damage, float projSpeed, float fireRate, int bulletsPerShot, float spreadArea) : CWeapon(parent)
{
	SetDamage(damage);
	SetProjSpeed(projSpeed);
	SetFireRate(fireRate);
	SetTarget(0);
	mBulletsPerShot = max(bulletsPerShot, 3);	//Ensures there is at least 3
	mSpreadArea = max(spreadArea, 0.0f);		//Ensures it is positive
}

void CShotGun::Fire()
{
	float additionRotation = mSpreadArea / 2.0f;
	float rotationDelta = (-mSpreadArea / static_cast<float>(mBulletsPerShot - 1));

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