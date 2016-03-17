#pragma once
#include "CWeapon.h"

class CShotGun : public CWeapon
{
private:
	virtual void Fire();

public:
	CShotGun(IEntity* parent, int damage, float projSpeed, float fireRate);
};