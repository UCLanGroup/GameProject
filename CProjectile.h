#pragma once
#include <TL-Engine.h>
#include "ICollidable.h"
#include "IResource.h"

class CProjectile : public ICollidable, public IResource
{
private:
	int mDamage;
	float mSpeed;
	tle::IMesh* mMesh;
	tle::IModel* mModel;

public:
	CProjectile();
	CProjectile(tle::IMesh* mesh, float* matrix, int damage, float speed);

	void Update(float delta);

	//Gets
	int GetDamage();
	float GetSpeed();
	tle::IModel* GetModel();
	bool IsOutOfBounds();

	//Sets
	void SetDamage(int damage);
	void SetSpeed(float speed);
	void SetMatrix(float* matrix);

	//Inherited from ICollidable
	virtual Vector3 GetCenterPoint();
	virtual bool GetMeshAndMatrix(tle::IMesh* mesh, float* matrix);

	//Inherited from IResource
	virtual void Hide();
	virtual void Reset();

	~CProjectile();
};