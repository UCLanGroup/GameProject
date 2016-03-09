#pragma once
#include "CVector3.h"
#include <Mesh.h>

class ICollidable
{
private:
	float mRadius;
public:
	virtual float GetRadius() { return mRadius; }
	virtual void SetRadius(float radius) { mRadius = radius; }
	
	virtual tlx::CVector3 GetCenterPoint() = 0;

	virtual tle::IMesh* GetMesh() = 0;

	virtual bool GetMatrix(float* matrix) = 0;
};