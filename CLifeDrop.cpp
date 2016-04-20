#include "CLifeDrop.h"

//Only requires the drop's texture
CLifeDrop::CLifeDrop(const string& texture)
{
	SetMesh(PARTICLE_MODEL, texture);
	mModel->ResetScale();
	mModel->Scale(kDropScale);
	SetRadius(kDropScale);
	SetExplodeable(false);
}

//Updates the drop
void CLifeDrop::Update(float delta)
{
	mModel->MoveZ(-delta * kDropSpeed);
}

//Applies the powerup/bonus to the player
void CLifeDrop::ApplyDrop(CPlayer* player)
{
	player->GainLife();
	SetDead(true);
}

//Ensures clean up of member variables
CLifeDrop::~CLifeDrop()
{
}