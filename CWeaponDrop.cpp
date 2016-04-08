#include "CWeaponDrop.h"

//Takes a weapon to create the drop
CWeaponDrop::CWeaponDrop(CWeapon* weapon, float duration)
{
	mpWeapon = weapon;
	mDuration = duration;
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