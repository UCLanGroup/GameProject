#pragma once
#include "IDrop.h"

//A powerup drop that heals the player
class CHealthDrop : public IDrop
{
private:
	int mHealAmount;
public:
	//Takes health amount
	CHealthDrop(const string& texture, int healAmount = 50);

	//Updates the drop
	virtual void Update(float delta);

	//Applies the powerup/bonus to the player
	virtual void ApplyDrop(CPlayer* player);

	//Ensures clean up of member variables
	~CHealthDrop();
};