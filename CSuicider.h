#pragma once
#include "CEnemy.h"

class CSuicider : public CEnemy
{
private:

public:
	CSuicider(std::vector<CPlayer*>* players, BulletList* playerBullets, BulletList* enemyBullets);

	virtual void Move(float delta);
	virtual void Update(float delta);
	virtual void Reset();
};