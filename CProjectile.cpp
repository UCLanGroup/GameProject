#include "CProjectile.h"
#include "Globals.h"
#include "CMeshCache.h"

CProjectile::CProjectile()
{
	mMesh = CMeshCache::GetInstance()->LoadMesh(BULLET_MESH);
	mModel = mMesh->CreateModel();
	//mModel->SetMatrix(matrix);

	mDamage = 0;
	mSpeed = 0.0;
	mRadius = 2.0f;
}

//The matrix should be the matrix gained from the parent model (the plane/spaceship)
//This will give the projectile the exact same rotation and location as the parent
CProjectile::CProjectile(tle::IMesh* mesh, float* matrix, int damage, float speed)
{
	mMesh = mesh;
	mModel = mMesh->CreateModel();
	mModel->SetMatrix(matrix);

	mDamage = damage;
	mSpeed = speed;
	mRadius = 2.0f;
}

void CProjectile::Update(float delta)
{
	mModel->MoveLocalZ(delta * mSpeed);
}

bool CProjectile::CheckCollision()
{
	return false; //No collision check atm
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
}

CProjectile::~CProjectile()
{
	if (gEngine != 0 && mMesh != 0)
	{
		mMesh->RemoveModel(mModel);
	}
}