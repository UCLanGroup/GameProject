#pragma once
#include "CEnemy.h"

class CEnemyBoss : public CEnemy
{
private:
	enum State { Enter, Attack1, Attack2, Overdrive };
protected:
	State mState;
	float mBobbing;
public:
	CEnemyBoss();

	virtual void Move(float delta);
	virtual void Update(float delta);
	virtual void TakeDamage(int damage);
	virtual void Reset();
};