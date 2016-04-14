#pragma once
#include "CWeapon.h"

class CMissileBarrage : public CWeapon
{
private:
	BulletList* mpEnemyProjectiles;

	virtual void Fire();

public:
	CMissileBarrage(IEntity* parent, int damage, float projSpeed, float fireRate);

	void SetEnemyBulletList(BulletList* pBulletList);
};