#include "CPlayer.h"

void CPlayer::Init()
{
	mMesh = gEngine->LoadMesh(PLAYERMESH);
	model = mMesh->CreateModel(0.0f, 0.0f, 0.0f);
	IMesh* bulletMesh = gEngine->LoadMesh(BULLET_MESH);
	mWeapon.reset(new CWeapon(model, bulletMesh, 1, 100.0f, 0.1f));
}

void CPlayer::Move(float dt)
{
	if (gEngine->KeyHeld(KEY_UP))
	{
		model->MoveZ(mSpeed * dt);
		if (model->GetZ() > AREA_BOUNDS_TOP)
		{
			model->SetZ(AREA_BOUNDS_TOP);
		}
	}
	if (gEngine->KeyHeld(KEY_DOWN))
	{
		model->MoveZ(-mSpeed * dt);
		if (model->GetZ() < AREA_BOUNDS_BOTTOM)
		{
			model->SetZ(AREA_BOUNDS_BOTTOM);
		}
	}
	if (gEngine->KeyHeld(KEY_LEFT))
	{
		model->MoveX(-mSpeed * dt);
		if (model->GetX() < AREA_BOUNDS_LEFT)
		{
			model->SetX(AREA_BOUNDS_LEFT);
		}
	}
	if (gEngine->KeyHeld(KEY_RIGHT))
	{
		model->MoveX(mSpeed * dt);
		if (model->GetX() > AREA_BOUNDS_RIGHT)
		{
			model->SetX(AREA_BOUNDS_RIGHT);
		}
	}
}

CWeapon* CPlayer::GetWeapon()
{
	return mWeapon.get();
}

//Inherited from ICollidable
Vector3 CPlayer::GetCenterPoint()
{
	return Vector3(model->GetX(), model->GetY(), model->GetZ());
}

bool CPlayer::GetMeshAndMatrix(IMesh* mesh, float* matrix)
{
	//Check if mesh and model exists
	if (mMesh == 0 || model == 0)
	{
		return false;
	}

	mesh = mMesh;
	model->GetMatrix(matrix); //Fills in the matrix

	return true;
}

CPlayer::~CPlayer()
{
	//mesh->RemoveModel(model);
	//gEngine->RemoveMesh(mesh);
}
