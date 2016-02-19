#pragma once
#include <TL-Engine.h>
#include "IEntity.h"

class CProjectile : public IEntity
{
private:
	int mDamage;
	float mSpeed;

public:
	CProjectile();
	CProjectile(tle::IMesh* mesh, float* matrix, int damage, float speed);

	void Update(float delta);
	virtual void CheckCollision();

	//Gets
	int GetDamage();
	float GetSpeed();

	//Sets
	void SetDamage(int damage);
	void SetSpeed(float speed);
	void SetMatrix(float* matrix);

	//Inherited from IEntity : IResource
	virtual void Reset();

	~CProjectile();
};