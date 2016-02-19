#pragma once
#include <TL-Engine.h>
#include "Vector3.h"

class ICollidable;

class ICollider
{
public:
	virtual bool CheckCollision() = 0;

	//Allow for custom collision
	virtual bool CollidesSphere(ICollidable* collidable) = 0;
	virtual bool CollidesMesh(ICollidable* collidable) = 0;

protected:
	//Collision methods
	bool CollideSphere(Vector3& p1, Vector3& p2, float r1, float r2);
	bool CollideMesh(tle::IMesh* me1, tle::IMesh* me2, float* ma1, float* ma2);
};