#define _USE_MATH_DEFINES
#include "CBlaster.h"
#include "CBullet.h"
#include "NETTIK_Networking.hpp"
using namespace NETTIK;

CBlaster::CBlaster(IEntity* parent, int damage, float projSpeed, float fireRate) : CWeapon(parent)
{
	SetMaxLevel(3);
	SetLevel(1);
	SetDamage(damage);
	SetProjSpeed(projSpeed);
	SetFireRate(fireRate);
	SetTarget(0);
}

CBaseProjectile* CBlaster::CreateBullet()
{
	float matrix[16];
	GetParent()->GetMatrix(matrix);

	CBullet* bullet = new CBullet();
	bullet->Init();
	bullet->SetMatrix(matrix);

	//If there's a target then fire directly at the target
	if (GetTarget())
	{
		CVector3 targetPos = GetTarget()->GetCenterPoint();
		CVector3 parentPos = GetParent()->GetCenterPoint();

		CVector3 dif = targetPos - parentPos;

		//Calculate the bearing from north
		float rotation = 90.0f - atan2f(dif.z, dif.x) * (180.0f / static_cast<float>(M_PI));

		bullet->SetRotation(rotation);
	}

	bullet->SetDamage(GetDamage());
	bullet->SetSpeed(GetProjSpeed());
	bullet->SetParent(GetParent());
	bullet->SetExplodeable(true);
	
	return bullet;
}

void CBlaster::Fire()
{
	CBaseProjectile* bullet;

	//Create a different set of bullets depending on weapon level
	switch(GetLevel())
	{
	case 1:
		//One bullet centered
		bullet = CreateBullet();
		GetBulletList()->push_back(unique_ptr<CBaseProjectile>(bullet));
		break;

	case 2:
		//Two bullets, both slightly off center to either side
		bullet = CreateBullet();
		bullet->GetModel()->MoveLocalX(3.0f); //Slightly to the right
		GetBulletList()->push_back(unique_ptr<CBaseProjectile>(bullet));

		bullet = CreateBullet();
		bullet->GetModel()->MoveLocalX(-3.0f); //Slightly to the left
		GetBulletList()->push_back(unique_ptr<CBaseProjectile>(bullet));
		break;

	case 3:
		//Three bullets, two slightly off center to either side, one centered
		bullet = CreateBullet();
		bullet->GetModel()->MoveLocalX(6.0f); //Slightly to the right
		GetBulletList()->push_back(unique_ptr<CBaseProjectile>(bullet));

		bullet = CreateBullet();
		bullet->GetModel()->MoveLocalZ(3.0f); //Slightly forward
		GetBulletList()->push_back(unique_ptr<CBaseProjectile>(bullet));

		bullet = CreateBullet();
		bullet->GetModel()->MoveLocalX(-6.0f); //Slightly to the left
		GetBulletList()->push_back(unique_ptr<CBaseProjectile>(bullet));
		break;

	default:
		break;

	}
}