#include "CHaloBoss.h"
#include "CPlayer.h"

const int kOverdriveLimit = 300;

const float kMissileAttackDuration = 7.0f;
const float kBlasterAttackDuration = 7.0f;
const float kWaveAttackDuration = 7.0f;
const float kRotateSpeed = 50.0f;
const float kRotorSpeed = 720.0f;
const float kSpinSpeed = 50.0f;
const float kRadius = 30.0f;
const CVector3 kTopPos = { 0.0f, 0.0f, AREA_BOUNDS_TOP - 1.1f * kRadius };
const CVector3 kCenterPos = { (AREA_BOUNDS_RIGHT + AREA_BOUNDS_LEFT) / 2.0f, 0.0f, (AREA_BOUNDS_TOP + AREA_BOUNDS_BOTTOM) / 2.0f };

CHaloBoss::CHaloBoss(std::vector<CPlayer*>* players, BulletList* playerBullets, BulletList* enemyBullets) : CEnemy(players, playerBullets, enemyBullets)
{
	//Model
	SetMesh(HALO_BOSS_MESH);
	mModel->ResetScale();
	mModel->ResetOrientation();
	mModel->Scale(1.8f);
	mModel->RotateLocalY(180.0f);

	//Stats
	SetHealth(1000);
	SetRadius(kRadius);
	SetSpeed(30.0f);
	SetValue(1000);
	mStateTimer = 0.0f;
	mState = State::MoveTop;

	//Weapons
	mBlaster.reset(new CBlaster(this, 5, 100.0f, 0.05f));
	mBlaster->SetBulletList(enemyBullets);
	mBlaster->SetLevel(2);

	mLeftMissileBarrage.reset(new CMissileBarrage(this, 10, 50.0f, 0.2f));
	mLeftMissileBarrage->SetRotation(90.0f);
	mLeftMissileBarrage->SetBulletList(enemyBullets);
	mLeftMissileBarrage->SetEnemyBulletList(playerBullets);

	mRightMissileBarrage.reset(new CMissileBarrage(this, 10, 50.0f, 0.2f));
	mRightMissileBarrage->SetRotation(-90.0f);
	mRightMissileBarrage->SetBulletList(enemyBullets);
	mRightMissileBarrage->SetEnemyBulletList(playerBullets);

	mShotGun.reset(new CShotGun(this, 10, 100.0f, 0.4f, 19, 360.0f));
	mShotGun->SetBulletList(enemyBullets);

	if (static_cast<int>(players->size()) > 0)
	{
		mRightMissileBarrage->SetTarget((*players)[0]);
		mLeftMissileBarrage->SetTarget((*players)[0]);
		mShotGun->SetTarget((*players)[0]);
	}
}

void CHaloBoss::Move(float delta)
{

}

void CHaloBoss::Update(float delta)
{
	//Rotate rotor
	(mModel->GetNode(5))->RotateY(delta * kRotorSpeed);

	//State timer updates
	if (GetHealth() < kOverdriveLimit)
	{
		delta *= 2.0f;
	}
	mStateTimer += delta;

	//Weapon updates
	mBlaster->Update(delta);
	mShotGun->Update(delta);
	mRightMissileBarrage->Update(delta);
	mLeftMissileBarrage->Update(delta);

	float xDif = GetRadius() * 2.0f;

	//State transitions
	switch (mState)
	{
	case State::MoveCenter:
		if (MoveDirectlyTowards(kCenterPos, delta))
		{
			mState = State::WaveAttack;
			mShotGun->SetFiring(true);
			mStateTimer = 0.0f;
		}
		break;

	case State::MoveTop:
		if (MoveDirectlyTowards(kTopPos, delta) & RotateTowards(kCenterPos, delta * kRotateSpeed))
		{
			mState = State::MissileAttack;
			mRightMissileBarrage->SetFiring(true);
			mLeftMissileBarrage->SetFiring(true);
			mStateTimer = 0.0f;
		}
		break;

	case State::BlasterAttack:
		RotateTowards((*mpPlayers)[0]->GetCenterPoint(), delta * kRotateSpeed);
		if (mStateTimer > kBlasterAttackDuration)
		{
			mState = State::MoveTop;
			mBlaster->SetFiring(false);
			mStateTimer = 0.0f;
		}
		break;

	case State::MissileAttack:

		//Find smallest xDif from a player
		for (auto player = mpPlayers->begin(); player != mpPlayers->end(); player++)
		{
			CVector3 locDif = (*player)->GetCenterPoint() - GetCenterPoint();
			if (abs(locDif.x) < abs(xDif))
			{
				xDif = locDif.x;
			}
		}

		if (abs(xDif) < GetRadius()) //Check if player is below
		{
			if (xDif > 0.0f) //Dodge left
			{
				if (AREA_BOUNDS_LEFT < mModel->GetX() - GetRadius())
				{
					mModel->MoveX(GetSpeed() * -delta);
				}
			}
			else //Dodge right
			{
				if (AREA_BOUNDS_RIGHT > mModel->GetX() + GetRadius())
				{
					mModel->MoveX(GetSpeed() * delta);
				}
			}
		}

		if (mStateTimer > kMissileAttackDuration)
		{
			mState = State::MoveCenter;
			mRightMissileBarrage->SetFiring(false);
			mLeftMissileBarrage->SetFiring(false);
			mStateTimer = 0.0f;
		}
		break;

	case State::WaveAttack:
		if (mStateTimer > kWaveAttackDuration)
		{
			mState = State::BlasterAttack;
			mShotGun->SetFiring(false);
			mBlaster->SetFiring(true);
			mStateTimer = 0.0f;
		}
		break;

	default:
		break;
	}
}

void CHaloBoss::Reset()
{

}