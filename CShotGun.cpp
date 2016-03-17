#define _USE_MATH_DEFINES
#include "CShotGun.h"
#include "CProjectile.h"
#include "CMatrix4x4.h"

CShotGun::CShotGun(IEntity* parent, int damage, float projSpeed, float fireRate) : CWeapon(parent)
{
	SetDamage(damage);
	SetProjSpeed(projSpeed);
	SetFireRate(fireRate);
	SetTarget(0);
}

void CShotGun::Fire()
{

	tlx::CMatrix4x4 matrix;
	GetParent()->GetMatrix(matrix.m);

	tlx::CMatrix4x4 rot;
	rot.SetRotationY(30.0f / (180.0f / static_cast<float>(M_PI)));

	matrix *= rot;

	rot.SetRotationY(-15.0f / (180.0f / static_cast<float>(M_PI)));

	CProjectile* bullet = 0;

	for (int i = 0; i < 5;  i++)
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