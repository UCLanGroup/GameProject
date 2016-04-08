#include "CUpgradeDrop.h"

//Takes a weapon to create the drop
CUpgradeDrop::CUpgradeDrop(const string& texture)
{
	SetMesh(PARTICLE_MODEL, texture);
	mModel->ResetScale();
	mModel->Scale(kDropScale);
	SetRadius(kDropScale);
	SetExplodeable(false);
}

//Updates the drop
void CUpgradeDrop::Update(float delta)
{
	mModel->MoveZ(-delta * kDropSpeed);
}

//Applies the powerup/bonus to the player
void CUpgradeDrop::ApplyDrop(CPlayer* player)
{
	//Upgrade the weapon's main weapon
	player->GetMainWeapon()->Upgrade();
	SetDead(true);
}

//Ensures clean up of member variables
CUpgradeDrop::~CUpgradeDrop()
{
}