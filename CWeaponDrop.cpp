#include "CWeaponDrop.h"

const float kDropScale = 3.0f;
const float kDropSpeed = 20.0f;

//Takes a weapon to create the drop
CWeaponDrop::CWeaponDrop(CWeapon* weapon, const string& texture, float duration)
{
	mpWeapon = weapon;
	mDuration = duration;
	SetMesh(PARTICLE_MODEL, texture);
	mModel->Scale(kDropScale);
	SetRadius(kDropScale);
}

//Updates the drop
void CWeaponDrop::Update(float delta)
{
	mModel->MoveZ(-delta * kDropSpeed);
}

//Applies the powerup/bonus to the player
void CWeaponDrop::ApplyDrop(CPlayer* player)
{
	//Set the player's weapon
	player->SetBonusWeapon(mpWeapon, mDuration);
	mpWeapon = 0;
}

//Ensures clean up of member variables
CWeaponDrop::~CWeaponDrop()
{
	//Delete the weapon if the drop still contains it
	if (mpWeapon)
	{
		delete mpWeapon;
	}
}