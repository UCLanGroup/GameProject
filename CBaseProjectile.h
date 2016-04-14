#pragma once
#include <IEngine.h>
#include "IEntity.h"

class CBaseProjectile : public IEntity
{
protected:
	IEntity* mParent;

	int mDamage;
	float mSpeed;
	float mScale = 0.3f;
	bool mInitialized = false;

public:
	CBaseProjectile();

	virtual void Init() = 0;
	virtual void Cleanup() = 0;

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

	virtual ~CBaseProjectile();
};