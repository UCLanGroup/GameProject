#define _USE_MATH_DEFINES
#include "CBlaster.h"
#include "CProjectile.h"


CBlaster::CBlaster(IEntity* parent, int damage, float projSpeed, float fireRate) : CWeapon(parent)
{
	SetDamage(damage);
	SetProjSpeed(projSpeed);
	SetFireRate(fireRate);
	SetTarget(0);
}

void CBlaster::Fire()
{
	CProjectile* bullet = new CProjectile();

	float matrix[16];
	GetParent()->GetMatrix(matrix);
	bullet->SetMatrix(matrix);

	if (GetTarget())
	{
		CVector3 targetPos = GetTarget()->GetCenterPoint();
		CVector3 parentPos = GetParent()->GetCenterPoint();

		CVector3 dif = targetPos - parentPos;

		float rotation = 90.0f - atan2f(dif.z, dif.x) * (180.0f / static_cast<float>(M_PI));

		bullet->SetRotation(rotation);
	}

	bullet->SetDamage(GetDamage());
	bullet->SetSpeed(GetProjSpeed());
	bullet->SetParent(GetParent());

	GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));
}