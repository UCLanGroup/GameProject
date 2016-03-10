#pragma once
#include <Mesh.h>
#include "CVector3.h"

class ICollidable;

class ICollider
{
public:
	virtual void CheckCollision() = 0;

	//Allow for custom collision
	virtual bool CollidesSphere(ICollidable* collidable) = 0;
	virtual bool CollidesMesh(ICollidable* collidable) = 0;

protected:
	//Collision methods
	bool CollideSphere(tlx::CVector3& p1, tlx::CVector3& p2, float r1, float r2);
	bool CollideMesh(tle::IMesh* me1, tle::IMesh* me2, float* ma1, float* ma2);
};