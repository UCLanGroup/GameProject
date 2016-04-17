#include "CMissileBarrage.h"
#include "CMissile.h"

CMissileBarrage::CMissileBarrage(IEntity* parent, int damage, float projSpeed, float fireRate) : CWeapon(parent)
{
	SetDamage(damage);
	SetProjSpeed(projSpeed);
	SetFireRate(fireRate);
	SetTarget(0);
	mpEnemyProjectiles = 0;
}

void CMissileBarrage::SetEnemyBulletList(BulletList* bulletList)
{
	mpEnemyProjectiles = bulletList;
}

void CMissileBarrage::Fire()
{
	float offsetMagnitude = static_cast<float>(rand() % 21 - 10);

	CMissile* missile = CreateProjectile<CMissile>(true);

	missile->GetModel()->MoveLocalX(offsetMagnitude);
	missile->SetLists(mpEnemyProjectiles);
	missile->SetTarget(GetTarget()); //If target is zero then the missile will just fly forward

	GetBulletList()->push_back(unique_ptr<CProjectile>(missile));
}