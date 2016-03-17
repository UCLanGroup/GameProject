#include "CMissileLauncher.h"
#include "CMissile.h"

CMissileLauncher::CMissileLauncher(IEntity* parent, int damage, float projSpeed, float fireRate) : CWeapon(parent)
{
	SetDamage(damage);
	SetProjSpeed(projSpeed);
	SetFireRate(fireRate);
	SetTarget(0);
}

void CMissileLauncher::SetEnemyBulletList(BulletList* bulletList)
{
	mpEnemyProjectiles = bulletList;
}

void CMissileLauncher::Fire()
{
	CMissile* missile = new CMissile();
	missile->SetPosition(GetParent()->GetCenterPoint());
	missile->SetRotation(GetParent()->GetRotation());
	missile->SetTarget(GetTarget());
	missile->SetLists(mpEnemyProjectiles);

	missile->SetDamage(GetDamage());
	missile->SetSpeed(GetProjSpeed());
	missile->SetParent(GetParent());

	GetBulletList()->push_back(unique_ptr<CProjectile>(missile));
}