#pragma once
#include "Vector3.h"
#include <TL-Engine.h>

class ICollidable
{
private:
	float mRadius;
public:
	virtual float GetRadius() { return mRadius; }
	virtual void SetRadius(float radius) { mRadius = radius; }
	
	virtual Vector3 GetCenterPoint() = 0;

	virtual tle::IMesh* GetMesh() = 0;

	virtual bool GetMatrix(float* matrix) = 0;
};