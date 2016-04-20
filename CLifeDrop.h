#pragma once
#include "IDrop.h"

//A powerup that gives the player an extra life
class CLifeDrop : public IDrop
{
public:
	//Only requires the drop's texture
	CLifeDrop(const string& texture);

	//Updates the drop
	virtual void Update(float delta);

	//Applies the powerup/bonus to the player
	virtual void ApplyDrop(CPlayer* player);

	//Ensures clean up of member variables
	~CLifeDrop();
};