#pragma once
#include "CWeapon.h"

class CShotGun : public CWeapon
{
private:
	int mBulletsPerShot;

	virtual void Fire();

public:
	CShotGun(IEntity* parent, int damage, float projSpeed, float fireRate, int bulletsPerShot);
};