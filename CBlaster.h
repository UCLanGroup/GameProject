#pragma once
#include "CWeapon.h"

class CBlaster : public CWeapon
{
private:
	virtual void Fire();

public:
	CBlaster(IEntity* parent, int damage, float projSpeed, float fireRate);
	CProjectile* CreateBullet();
};