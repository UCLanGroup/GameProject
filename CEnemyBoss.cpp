#define _USE_MATH_DEFINES
#include "CEnemyBoss.h"
#include "CPlayer.h"
#include "CMissile.h"

const float kRotateSpeed = 720.0f; //Rotation Speed
const float kAttackRate = 0.5f;
const float kStateDuration = 5.0f; //Each state lasts for 5 seconds

CEnemyBoss::CEnemyBoss(std::vector<CPlayer*>* players, BulletList* playerBullets, BulletList* enemyBullets) : CEnemy(players, playerBullets, enemyBullets)
{
	SetMesh(HAVOC_BOSS_MESH);
	mModel->ResetScale();
	mModel->ResetOrientation();
	mModel->Scale(2.0f);
	mModel->RotateLocalY(180.0f);
	SetValue(500);

	mBlaster.reset(new CBlaster(this, 10, 100.0f, 0.5f));
	mBlaster->SetBulletList(enemyBullets);

	mMissileLauncher.reset( new CMissileLauncher(this, 10, 50.0f, 0.5f) );
	mMissileLauncher->SetBulletList(enemyBullets);
	mMissileLauncher->SetEnemyBulletList(playerBullets);
	mMissileLauncher->SetFiring(true);

	if (static_cast<int>(players->size()) > 0)
	{
		mBlaster->SetTarget((*players)[0]);
		mMissileLauncher->SetTarget((*players)[0]);
	}

	Reset();
}

void CEnemyBoss::Move(float delta)
{
	//Custom movement
	if (mState == State::Enter)
	{
		//Move downwards
		mModel->MoveZ(GetSpeed() * -delta);

		if (AREA_BOUNDS_TOP - (2.0f * GetRadius()) > mModel->GetZ())
		{
			mState = State::Attack1;
		}
	}
	else //All other states
	{
		//Bobbing up and down
		mBobbing += delta;
		if(delta > (2.0f * M_PI)) mBobbing = 0.0f;

		float bobAmount = sin(mBobbing) * GetRadius() * 0.5f;

		mModel->SetZ(AREA_BOUNDS_TOP - (2.0f * GetRadius()) + bobAmount);

		//Avoid the closest player

		float xDif = GetRadius() * 2.0f;

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
				else
				{
					mModel->MoveX(GetSpeed() * delta);
				}
			}
			else //Dodge right
			{
				if (AREA_BOUNDS_RIGHT > mModel->GetX() + GetRadius())
				{
					mModel->MoveX(GetSpeed() * delta);
				}
				else
				{
					mModel->MoveX(GetSpeed() * -delta);
				}
			}
		}
	}
}

void CEnemyBoss::Update(float delta)
{
	if (mState == State::Overdrive) delta *= 2.0f;
	Move(delta);
	if (mModel->GetNumNodes() > 1)
		(mModel->GetNode(6))->RotateY(delta * kRotateSpeed); //Rotate spinny thing
	if (mState == State::Enter) return; //Don't do anything when entering

	mBlaster->Update(delta);
	mMissileLauncher->Update(delta);

	mStateTimer += delta;

	if (mState == State::Attack1 && mStateTimer > kStateDuration)
	{
		mStateTimer -= kStateDuration;
		mBlaster->SetFiring(true);
		mMissileLauncher->SetFiring(false);
		mState = State::Attack2;
	}
	else if (mState == State::Attack2 && mStateTimer > kStateDuration)
	{
		mStateTimer -= kStateDuration;
		mBlaster->SetFiring(false);
		mMissileLauncher->SetFiring(true);
		mState = State::Attack1;
	}
}

void CEnemyBoss::TakeDamage(int damage)
{
	//Take damage? Potential invulnerable state
	SetHealth( GetHealth() - damage );

	if (GetHealth() < 60)
	{
		mState = State::Overdrive;
		mBlaster->SetFiring(true);
		mMissileLauncher->SetFiring(true);
	}
	if (GetHealth() <= 0)
	{
		SetDead(true);
		mFinished = true;
	}
}

void CEnemyBoss::Reset()
{
	mModel->SetPosition(0.0f, 0.0f, AREA_BOUNDS_TOP + 20.0f);
	SetHealth(400);
	SetRadius(20.0f);
	SetSpeed(20.0f);
	mBobbing = 0.0f;
	mStateTimer = 0.0f;
	mState = State::Enter;
}

void CEnemyBoss::ActivateTheCage()
{
	SetMesh(PARTICLE_MODEL, NICK_CAGE);
	mModel->ResetScale();
	mModel->Scale(10.0f);
	mMissileLauncher->ActivateTheCage();
}