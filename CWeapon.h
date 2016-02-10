#pragma once
#include "Globals.h"
#include <vector>
#include <TL-Engine.h>
#include "CProjectile.h"

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

	void Update(float delta, vector_ptr<CProjectile>& projectiles);
};