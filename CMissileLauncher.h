#pragma once
#include "CWeapon.h"

class CMissileLauncher : public CWeapon
{
private:
	BulletList* mpEnemyProjectiles;
	IEntity* mpTarget;

	virtual CProjectile* Fire();

public:
	CMissileLauncher(IEntity* parent, int damage, float projSpeed, float fireRate);

	void SetTarget(IEntity* target);
	void SetEnemyBulletList(BulletList* pBulletList);
};