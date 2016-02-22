#pragma once
#include "CEnemy.h"

class CEnemyBoss : public CEnemy
{
private:
	enum State { Enter, Attack1, Attack2, Overdrive };
protected:
	State mState = State::Enter;
	float mBobbing = 0.0f;
	float mStateTimer = 0.0f;
	float mAttackTimer = 0.0f;
public:
	CEnemyBoss();

	virtual void Move(float delta);
	virtual void Update(float delta);
	virtual void TakeDamage(int damage);
	virtual void Reset();
};