#pragma once
#include "CWeapon.h"

class CChaosGun : public CWeapon
{
private:
	virtual void Fire();

public:
	CChaosGun(IEntity* parent, int damage, float projSpeed, float fireRate);
};