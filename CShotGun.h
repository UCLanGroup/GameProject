#pragma once
#include "CWeapon.h"

class CShotGun : public CWeapon
{
private:
	float mSpreadArea;
	int mBulletsPerShot;

	virtual void Fire();

public:
	CShotGun(IEntity* parent, int damage, float projSpeed, float fireRate, int bulletsPerShot = 5, float spreadArea = 60.0f);
};