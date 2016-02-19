#pragma once
#include "Globals.h"
#include <list>
#include <TL-Engine.h>
#include "CProjectile.h"
#include "CPool.h"

using BulletList = std::list<res_ptr<CProjectile>>;

class CWeapon
{
private:
	int mDamage;
	float mProjectileSpeed;
	float mFireRate;
	float mTimer;
	tle::IModel* mParent;
	tle::IMesh* mProjectileMesh;

public:
	CWeapon(tle::IModel* parent, tle::IMesh* mesh, int damage, float projSpeed, float fireRate);

	void Update(float delta, BulletList& projectiles);
};