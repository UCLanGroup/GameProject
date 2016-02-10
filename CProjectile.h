#pragma once
#include <TL-Engine.h>
#include "ICollidable.h"

class CProjectile : public ICollidable
{
private:
	int mDamage;
	float mSpeed;
	tle::IMesh* mMesh;
	tle::IModel* mModel;

public:
	CProjectile(tle::IMesh* mesh, float* matrix, int damage, float speed);

	void Update(float delta);

	int GetDamage();
	tle::IModel* GetModel();
	bool IsOutOfBounds();

	//Inherited from ICollidable

	virtual Vector3 GetCenterPoint();

	virtual bool GetMeshAndMatrix(tle::IMesh* mesh, float* matrix);

	~CProjectile();
};