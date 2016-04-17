#include "CMissileLauncher.h"
#include "CMissile.h"

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
	CMissile* missile = CreateProjectile<CMissile>(true);

	missile->SetLists(mpEnemyProjectiles);
	missile->SetTarget(GetTarget()); //If target is zero then the missile will just fly forward

	GetBulletList()->push_back(unique_ptr<CProjectile>(missile));
}