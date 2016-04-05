#define _USE_MATH_DEFINES
#include "CBlaster.h"
#include "CProjectile.h"


CBlaster::CBlaster(IEntity* parent, int damage, float projSpeed, float fireRate) : CWeapon(parent)
{
	SetMaxLevel(3);
	SetLevel(1);
	SetDamage(damage);
	SetProjSpeed(projSpeed);
	SetFireRate(fireRate);
	SetTarget(0);
}

CProjectile* CBlaster::CreateBullet()
{
	float matrix[16];
	GetParent()->GetMatrix(matrix);

	CProjectile* bullet = new CProjectile();

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

	return bullet;
}

void CBlaster::Fire()
{
	float matrix[16];
	GetParent()->GetMatrix(matrix);

	CProjectile* bullet;

	switch(GetLevel())
	{
	case 1:
		bullet = CreateBullet();
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));
		break;

	case 2:
		bullet = CreateBullet();
		bullet->GetModel()->MoveLocalX(3.0f);
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));

		bullet = CreateBullet();
		bullet->GetModel()->MoveLocalX(-3.0f);
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));
		break;

	case 3:
		bullet = CreateBullet();
		bullet->GetModel()->MoveLocalX(6.0f);
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));

		bullet = CreateBullet();
		bullet->GetModel()->MoveLocalZ(3.0f);
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));

		bullet = CreateBullet();
		bullet->GetModel()->MoveLocalX(-6.0f);
		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));
		break;

	default:
		break;

	}
}