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
	float matrix[16];
	GetParent()->GetMatrix(matrix);
	float offsetMagnitude = static_cast<float>(rand() % 21 - 10);

	CVector3 offset(matrix[0], matrix[1], matrix[2]);

	CMissile* missile = new CMissile();

	//Set the position and facing direction to the same as the parent entity
	missile->SetPosition(GetParent()->GetCenterPoint() + (offset * offsetMagnitude));
	missile->SetRotation(GetParent()->GetRotation());
	missile->SetLists(mpEnemyProjectiles);

	//If target is zero then the missile will just fly forward
	missile->SetTarget(GetTarget());

	missile->SetDamage(GetDamage());
	missile->SetSpeed(GetProjSpeed());
	missile->SetParent(GetParent());
	missile->SetExplodeable(true);

	GetBulletList()->push_back(unique_ptr<CProjectile>(missile));
}