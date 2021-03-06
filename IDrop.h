#pragma once
#include "IEntity.h"
#include "CPlayer.h"

//Shared interface between dropped powerups and other modifiers/bonuses
class IDrop : public IEntity
{
protected:
	const float kDropScale = 3.0f;
	const float kDropSpeed = 20.0f;

public:
	//Updates the drop
	virtual void Update(float delta) = 0;

	//Applies the powerup/bonus to the player
	virtual void ApplyDrop(CPlayer* player) = 0;

	//Inherited from IEntity - Not needed for drops
	virtual void CheckCollision() { /*Does nothing*/ };

	//Inherited from IEntity - Not needed for drops
	virtual void Reset() { /*Does nothing*/ };

};