#pragma once
#include "CWeapon.h"

class CBlaster : public CWeapon
{
private:
	BulletList* mpEnemyProjectiles;
	IEntity* mpTarget;

	virtual CProjectile* Fire();

public:
	CBlaster(IEntity* parent, int damage, float projSpeed, float fireRate);
};