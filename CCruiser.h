#pragma once
#include "CEnemy.h"
#include "CMissileBarrage.h"

class CCruiser : public CEnemy
{
private:
	enum State { Enter, Attack, Rotate };
	State mState = State::Enter;
	float mStateTimer = 0.0f;

	unique_ptr<CMissileBarrage> mWeapon;

public:
	CCruiser(std::vector<CPlayer*>* players, BulletList* playerBullets, BulletList* enemyBullets);

	virtual void Move(float delta);
	virtual void Update(float delta);
	virtual void Reset();
};