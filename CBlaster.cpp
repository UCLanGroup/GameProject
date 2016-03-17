#include "CBlaster.h"
#include "CProjectile.h"

CBlaster::CBlaster(IEntity* parent, int damage, float projSpeed, float fireRate) : CWeapon(parent)
{
	SetDamage(damage);
	SetProjSpeed(projSpeed);
	SetFireRate(fireRate);
}

CProjectile* CBlaster::Fire()
{
	CProjectile* bullet = new CProjectile();

	float matrix[16];
	GetParent()->GetMatrix(matrix);
	bullet->SetMatrix(matrix);

	return bullet;
}