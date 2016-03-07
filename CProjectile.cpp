#include "CProjectile.h"
#include "Globals.h"
#include "CMeshCache.h"

CProjectile::CProjectile()
{
	SetMesh(BULLET_MESH);
	//mModel->SetMatrix(matrix);

	mDamage = 1;
	mSpeed = 50.0;
	SetRadius(2.0f);
	SetDead(false);
}

//The matrix should be the matrix gained from the parent model (the plane/spaceship)
//This will give the projectile the exact same rotation and location as the parent
CProjectile::CProjectile(tle::IMesh* mesh, float* matrix, int damage, float speed)
{
	SetMesh(mesh);
	SetMatrix(matrix);

	mDamage = damage;
	mSpeed = speed;
	SetRadius(2.0f);
	SetDead(false);
}

void CProjectile::Update(float delta)
{
	mModel->MoveLocalZ(delta * mSpeed);
}

void CProjectile::CheckCollision()
{
	//No collision check atm
}

//Gets

int CProjectile::GetDamage()
{
	return mDamage;
}

float CProjectile::GetSpeed()
{
	return mSpeed;
}

//Sets

void CProjectile::SetDamage(int damage)
{
	mDamage = damage;
}

void CProjectile::SetSpeed(float speed)
{
	mSpeed = speed;
}

void CProjectile::SetMatrix(float* matrix)
{
	mModel->SetMatrix(matrix);
}

//Inherited from IEntity : IResource

void CProjectile::Reset()
{
	//Empty
	SetDead(false);
}

CProjectile::~CProjectile()
{

}