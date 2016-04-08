#pragma once
#include "IDrop.h"

//A powerup drop that gives a different weapon
class CWeaponDrop : public IDrop
{
	CWeapon* mpWeapon;
	float mDuration;

public:
	//Takes a weapon to create the drop
	CWeaponDrop(CWeapon* weapon, float duration = 10.0f);

	//Applies the powerup/bonus to the player
	virtual void ApplyDrop(CPlayer* player);

	//Ensures clean up of member variables
	~CWeaponDrop();
};