#include "CMissileLauncher.h"
#include "CMissile.h"
#include "IController.hpp"
using namespace NETTIK;

CMissileLauncher::CMissileLauncher(IEntity* parent, int damage, float projSpeed, float fireRate) : CWeapon(parent)
{
	SetDamage(damage);
	SetProjSpeed(projSpeed);
	SetFireRate(fireRate);
	SetTarget(0);
	mpEnemyProjectiles = 0;
}

void CMissileLauncher::SetEnemyBulletList(BulletList* bulletList)
{
	mpEnemyProjectiles = bulletList;
}

void CMissileLauncher::Fire()
{
	CMissile* missile = new CMissile();
	missile->Init();

	//Set the position and facing direction to the same as the parent entity
	missile->SetPosition(GetParent()->GetCenterPoint());
	missile->SetRotation(GetParent()->GetRotation());
	missile->SetLists(mpEnemyProjectiles);

	//If target is zero then the missile will just fly forward
	missile->SetTarget(GetTarget());

	missile->SetDamage(GetDamage());
	missile->SetSpeed(GetProjSpeed());
	missile->SetParent(GetParent());
	missile->SetExplodeable(true);

	GetBulletList()->push_back(unique_ptr<CBaseProjectile>(missile));
}