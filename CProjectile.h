#pragma once
#include <IEngine.h>
#include "IEntity.h"

class CProjectile : public IEntity
{
private:
	IEntity* mParent;

	int mDamage;
	float mSpeed;
	float mScale = 0.3f;

public:
	CProjectile();
	CProjectile(tle::IMesh* mesh, float* matrix, int damage, float speed);

	virtual void Update(float delta);
	virtual void CheckCollision();

	//Gets
	int GetDamage();
	float GetSpeed();
	IEntity* GetParent();

	//Sets
	void SetDamage(int damage);
	void SetSpeed(float speed);
	void SetMatrix(float* matrix);
	void SetParent(IEntity* parent);

	//Inherited from IEntity : IResource
	virtual void Reset();

	virtual ~CProjectile();
};