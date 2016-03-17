#pragma once
#include "CWeapon.h"

class CMissileLauncher : public CWeapon
{
private:
	BulletList* mpEnemyProjectiles;

	virtual void Fire();

public:
	CMissileLauncher(IEntity* parent, int damage, float projSpeed, float fireRate);

	void SetEnemyBulletList(BulletList* pBulletList);
};