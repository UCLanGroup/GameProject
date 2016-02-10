#include "CPlayer.h"

void CPlayer::Init()
{
	mesh = gEngine->LoadMesh(PLAYERMESH);
	model = mesh->CreateModel(0.0f, 0.0f, 0.0f);
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

CPlayer::~CPlayer()
{
	//mesh->RemoveModel(model);
	//gEngine->RemoveMesh(mesh);
}
