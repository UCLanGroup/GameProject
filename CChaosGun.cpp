#define _USE_MATH_DEFINES
#include "CChaosGun.h"
#include "CProjectile.h"
#include "CMissile.h"
#include "CMatrix4x4.h"

CChaosGun::CChaosGun(IEntity* parent, int damage, float projSpeed, float fireRate) : CWeapon(parent)
{
	SetDamage(damage);
	SetProjSpeed(projSpeed);
	SetFireRate(fireRate);
	SetTarget(0);
}

void CChaosGun::Fire()
{
	float angle = static_cast<float>(rand() % 41 - 20);

	CProjectile* bullet = 0;

	if (rand() % 2 == 1)
	{

		bullet = new CProjectile();
		bullet->SetDamage(GetDamage());
	}
	else
	{
		bullet = new CMissile();
		bullet->SetDamage(GetDamage() * 5);
	}

	bullet->SetPosition(GetParent()->GetCenterPoint());
	bullet->SetRotation(GetParent()->GetRotation() + angle);
	bullet->SetSpeed(GetProjSpeed());
	bullet->SetParent(GetParent());

	GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));
}