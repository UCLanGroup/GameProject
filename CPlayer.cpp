#include "CPlayer.h"

void CPlayer::Init()
{
	mMesh = gEngine->LoadMesh(PLAYERMESH);
	model = mMesh->CreateModel(0.0f, 0.0f, 0.0f);
}

void CPlayer::Move(float dt)
{
	if (gEngine->KeyHeld(KEY_UP))
	{
		model->MoveZ(mSpeed * dt);
	}
	if (gEngine->KeyHeld(KEY_DOWN))
	{
		model->MoveZ(-mSpeed * dt);
	}
	if (gEngine->KeyHeld(KEY_LEFT))
	{
		model->MoveX(-mSpeed * dt);
	}
	if (gEngine->KeyHeld(KEY_RIGHT))
	{
		model->MoveX(mSpeed * dt);
	}
}

//Inherited from ICollidable
Vector3 CPlayer::GetCenterPoint()
{
	return Vector3(model->GetX(), model->GetY(), model->GetY());
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
