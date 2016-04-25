#pragma once
#include "CEnemy.h"
#include "CBlaster.h"
#include "CMissileBarrage.h"
#include "CShotGun.h"

class CHaloBoss : public CEnemy
{
private:
	enum State { MoveTop, MoveCenter, MissileAttack, BlasterAttack, WaveAttack };

	State mState = State::MoveTop;

	unique_ptr<CShotGun> mShotGun;
	unique_ptr<CBlaster> mBlaster;
	unique_ptr<CMissileBarrage> mLeftMissileBarrage;
	unique_ptr<CMissileBarrage> mRightMissileBarrage;
	
	float mStateTimer = 0.0f; //Isn't used for all states
public:
	CHaloBoss(std::vector<CPlayer*>* players, BulletList* playerBullets, BulletList* enemyBullets);

	virtual void Move(float delta);
	virtual void Update(float delta);
	virtual void Reset();

	//Nick Cage Mode
	virtual void ActivateTheCage();
};