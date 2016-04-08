#pragma once
#include "CVector3.h"
#include <Mesh.h>

class ICollidable
{
private:
	float mRadius;
	bool mCollidable = true;
public:
	virtual float GetRadius() { return mRadius; }
	virtual void SetRadius(float radius) { mRadius = radius; }

	virtual bool IsCollidable() { return mCollidable; }
	virtual void SetCollidable(bool collidable) { mCollidable = collidable; }
	
	virtual tlx::CVector3 GetCenterPoint() = 0;

	virtual tle::IMesh* GetMesh() = 0;

	virtual bool GetMatrix(float* matrix) = 0;
};