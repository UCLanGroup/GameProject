#pragma once
#include "IDrop.h"

//A powerup drop that upgrades the player's main weapon
class CUpgradeDrop : public IDrop
{
public:
	//No additional data required
	CUpgradeDrop(const string& texture);

	//Updates the drop
	virtual void Update(float delta);

	//Applies the powerup/bonus to the player
	virtual void ApplyDrop(CPlayer* player);

	//Ensures clean up of member variables
	~CUpgradeDrop();
};