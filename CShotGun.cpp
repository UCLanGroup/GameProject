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
	//Get the matrix of the entity that weild this weapon
	tlx::CMatrix4x4 matrix;
	GetParent()->GetMatrix(matrix.m);

	//Create a rotation matrix
	tlx::CMatrix4x4 rot;
	rot.SetRotationY(30.0f / (180.0f / static_cast<float>(M_PI)));

	//Rotate the parent's matrix away from the center
	matrix *= rot;

	//Update the rotation matrix to rotate in the opposite direction
	//The amount it rotates by is dependant on the number of bullets
	rot.SetRotationY((-60.0f / static_cast<float>(mBulletsPerShot - 1)) / (180.0f / static_cast<float>(M_PI)));

	CProjectile* bullet = 0;

	for (int i = 0; i < mBulletsPerShot;  i++)
	{
		//Create a bullet with the current matrix
		bullet = new CProjectile();
		bullet->SetMatrix(matrix.m);

		//Rotate the matrix so that the next bullet heads at a slightly different angle
		matrix *= rot;

		bullet->SetDamage(GetDamage());
		bullet->SetSpeed(GetProjSpeed());
		bullet->SetParent(GetParent());

		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));
	}
}