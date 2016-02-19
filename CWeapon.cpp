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

void CWeapon::Update(float delta, BulletList& projectiles)
{
	mTimer += delta;
	while (mTimer > mFireRate)
	{
		float matrix[16];
		mParent->GetMatrix(matrix);

		res_ptr<CProjectile> newBullet = move(CPool<CProjectile>::GetInstance()->GetRes());
		newBullet->SetMatrix(matrix);
		newBullet->SetDamage(mDamage);
		newBullet->SetSpeed(mProjectileSpeed);

		projectiles.push_back(move(newBullet));

		mTimer -= mFireRate;
	}
}