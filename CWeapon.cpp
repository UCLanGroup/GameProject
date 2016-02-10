#include "CWeapon.h"

CWeapon::CWeapon(tle::IModel* parent, tle::IMesh* mesh, int damage, float projSpeed, float fireRate)
{
	mParent = parent;
	mProjectileMesh = mesh;
	mDamage = damage;
	mProjectileSpeed = projSpeed;
	mFireRate = fireRate;
	mTimer = 0.0f;
}

void CWeapon::Update(float delta, vector_ptr<CProjectile>& projectiles)
{
	mTimer += delta;
	while (mTimer > mFireRate)
	{
		float matrix[16];
		mParent->GetMatrix(matrix);

		unique_ptr<CProjectile> p(new CProjectile(mProjectileMesh, matrix, mDamage, mProjectileSpeed));

		projectiles.push_back(move(p));

		mTimer -= mFireRate;
	}
}