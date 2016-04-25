#pragma once
#include "CEnemy.h"
#include "CBlaster.h"
#include "CMissileLauncher.h"

class CEnemyBoss : public CEnemy
{
private:
	enum State { Enter, Attack1, Attack2, Overdrive };

	unique_ptr<CBlaster> mBlaster;
	unique_ptr<CMissileLauncher> mMissileLauncher;

protected:
	State mState = State::Enter;
	float mBobbing = 0.0f;
	float mStateTimer = 0.0f;
public:
	CEnemyBoss(std::vector<CPlayer*>* players, BulletList* playerBullets, BulletList* enemyBullets);

	virtual void Move(float delta);
	virtual void Update(float delta);
	virtual void TakeDamage(int damage);
	virtual void Reset();

	//Nick Cage Mode
	virtual void ActivateTheCage();
};