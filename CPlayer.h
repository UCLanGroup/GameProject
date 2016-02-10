#pragma once

#include <TL-Engine.h>
#include "globals.h"
#include "ICollidable.h"

using namespace tle;

class CPlayer : public ICollidable
{
private:
	IMesh* mMesh;
	float mSpeed = 20.0f; // speed to move plane
	

public:
	IModel* model;

	void Init();

	void Move(float);

	//Inherited from ICollidable
	virtual Vector3 GetCenterPoint();
	virtual bool GetMeshAndMatrix(IMesh* mesh, float* matrix);

	~CPlayer();

protected:

};