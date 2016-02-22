#pragma once
#include "CProjectile.h"
#include "CPool.h"
#include <list>

class CMissile : public CProjectile
{
private:
	IEntity* mTarget = 0;
	bool mClockwise = false;
	float mRotation = 0.0f;
	float mTimer = 0.0f;

	std::list<res_ptr<CProjectile>>* mpPlayerBullets = 0;

public:
	CMissile();

	virtual void Update(float delta);
	virtual void CheckCollision();

	void SetTarget(IEntity* target);
	void SetRotation(float rotation);
	void SetLists(std::list<res_ptr<CProjectile>>* playerBullets);

	IEntity* GetTarget();
	float GetRotation();
	bool IsClockwise();

	virtual void Reset();
};