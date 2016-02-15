#include "CProjectile.h"
#include "Globals.h"

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

int CProjectile::GetDamage()
{
	return mDamage;
}

tle::IModel* CProjectile::GetModel()
{
	return mModel;
}

bool CProjectile::IsOutOfBounds()
{
	return  mModel->GetX() < AREA_BOUNDS_LEFT  ||
			mModel->GetX() > AREA_BOUNDS_RIGHT ||
			mModel->GetZ() > AREA_BOUNDS_TOP   ||
			mModel->GetZ() < AREA_BOUNDS_BOTTOM;
}

//Inherited from ICollidable

Vector3 CProjectile::GetCenterPoint()
{
	return Vector3(mModel->GetX(), mModel->GetY(), mModel->GetZ());
}

bool CProjectile::GetMeshAndMatrix(tle::IMesh* mesh, float* matrix)
{
	//Check if mesh and model exists
	if (mMesh == 0 || mModel == 0)
	{
		return false;
	}

	mesh = mMesh;
	mModel->GetMatrix(matrix); //Fills in the matrix

	return true;
}

CProjectile::~CProjectile()
{
	mMesh->RemoveModel(mModel);
}