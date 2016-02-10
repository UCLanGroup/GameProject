#pragma once
#include "Vector3.h"
#include <Mesh.h>

class ICollidable
{
protected:
	float mRadius;
public:
	float GetBoundingRadius();
	
	virtual Vector3 GetCenterPoint() = 0;

	virtual bool GetMeshAndMatrix(tle::IMesh* mesh, float* matrix) = 0;
	
	//Checks if the collidables bounding spheres collide
	bool CollidesSphere(ICollidable* collidable);

	//Mesh to Mesh collision
	bool CollidesMesh(ICollidable* collidable);
};