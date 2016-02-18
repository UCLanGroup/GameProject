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

//Gets

int CProjectile::GetDamage()
{
	return mDamage;
}

float CProjectile::GetSpeed()
{
	return mSpeed;
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

//Inherited from IResource

void CProjectile::Reset()
{
	//Empty
}

void CProjectile::Hide()
{
	mModel->SetPosition(OFF_SCREEN_X, OFF_SCREEN_Y, OFF_SCREEN_Z);
}

CProjectile::~CProjectile()
{
	if (gEngine != 0 && mMesh != 0)
	{
		mMesh->RemoveModel(mModel);
	}
}