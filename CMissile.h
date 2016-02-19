#pragma once
#include "CProjectile.h"
#include "CPool.h"
#include <list>

class CMissile : public CProjectile
{
private:
	IEntity* mTarget = 0;

	std::list<res_ptr<CProjectile>>* mpPlayerBullets = 0;

public:
	CMissile();

	virtual void Update(float delta);
	virtual void CheckCollision();

	void SetTarget(IEntity* target);
	void SetLists(std::list<res_ptr<CProjectile>>* playerBullets);

	virtual void Reset();
};