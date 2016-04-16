#include "CHealthDrop.h"

//Takes a weapon to create the drop
CHealthDrop::CHealthDrop(const string& texture, int healAmount)
{
	SetMesh(PARTICLE_MODEL, texture);
	mModel->ResetScale();
	mModel->Scale(kDropScale);
	SetRadius(kDropScale);
	SetExplodeable(false);

	mHealAmount = healAmount;
}

//Updates the drop
void CHealthDrop::Update(float delta)
{
	mModel->MoveZ(-delta * kDropSpeed);
}

//Applies the powerup/bonus to the player
void CHealthDrop::ApplyDrop(CPlayer* player)
{
	//Upgrade the weapon's main weapon
	player->SetHealth(mHealAmount + player->GetHealth());
	SetDead(true);
}

//Ensures clean up of member variables
CHealthDrop::~CHealthDrop()
{
}