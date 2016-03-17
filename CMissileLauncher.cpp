#include "CMissileLauncher.h"
#include "CMissile.h"

CMissileLauncher::CMissileLauncher(IEntity* parent, int damage, float projSpeed, float fireRate) : CWeapon(parent)
{
	SetDamage(damage);
	SetProjSpeed(projSpeed);
	SetFireRate(fireRate);
}

void CMissileLauncher::SetTarget(IEntity* target)
{
	mpTarget = target;
}

void CMissileLauncher::SetEnemyBulletList(BulletList* bulletList)
{
	mpEnemyProjectiles = bulletList;
}

CProjectile* CMissileLauncher::Fire()
{
	CMissile* missile = new CMissile();
	missile->SetPosition(GetParent()->GetCenterPoint());
	missile->SetRotation(GetParent()->GetRotation());
	missile->SetTarget(mpTarget);
	missile->SetLists(mpEnemyProjectiles);

	return missile;
}