#define _USE_MATH_DEFINES
#include "CEnemyBoss.h"
#include "CPlayer.h"
#include "CMissile.h"

const float kRotateSpeed = 720.0f; //Rotation Speed
const float kAttackRate = 0.5f;
const float kStateDuration = 5.0f; //Each state lasts for 5 seconds

CEnemyBoss::CEnemyBoss()
{
	SetMesh(HAVOC_BOSS_MESH);
	mModel->Scale(2.0f);
	mModel->RotateLocalY(180.0f);

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
	(mModel->GetNode(6))->RotateY(delta * kRotateSpeed); //Rotate spinny thing

	if (mState == State::Enter) return; //Don't do anything when entering

	mStateTimer += delta;
	mAttackTimer += delta;

	if (mState == State::Attack1)
	{
		//Basic attack pattern, switches to attack2 after set amount of time
		while (mAttackTimer > kAttackRate)
		{
			res_ptr<CMissile> newMissile = move(CPool<CMissile>::GetInstance()->GetRes());
			newMissile->SetPosition(GetCenterPoint());
			newMissile->SetRotation(GetRotation());
			newMissile->SetDamage(10);
			newMissile->SetTarget((*mpPlayers)[0]);
			newMissile->SetLists(mpPlayerBullets);

			res_ptr<CProjectile> newBullet(newMissile.release());

			mpEnemyBullets->push_back(move(newBullet));

			mAttackTimer -= kAttackRate;
		}

		if (mState == State::Attack1 && mStateTimer > kStateDuration)
		{
			mStateTimer -= kStateDuration;
			mState = State::Attack2;
		}
	}
	else if (mState == State::Attack2)
	{
		//Basic attack pattern, switches to attack1 after set amount of time
		while (mAttackTimer > kAttackRate)
		{
			res_ptr<CProjectile> newBullet = move(CPool<CProjectile>::GetInstance()->GetRes());
			newBullet->SetPosition(GetCenterPoint());
			newBullet->SetRotation(GetRotation());
			newBullet->SetSpeed(100.0f);
			newBullet->SetDamage(10);

			mpEnemyBullets->push_back(move(newBullet));

			mAttackTimer -= kAttackRate;
		}

		if (mState == State::Attack2 && mStateTimer > kStateDuration)
		{
			mStateTimer -= kStateDuration;
			mState = State::Attack1;
		}
	}
	else if (mState == State::Overdrive)
	{
		//Death, enters overdrive when low on health
		while (mAttackTimer > kAttackRate)
		{
			res_ptr<CProjectile> newBullet = move(CPool<CProjectile>::GetInstance()->GetRes());
			newBullet->SetPosition(GetCenterPoint());
			newBullet->SetRotation(GetRotation());
			newBullet->SetSpeed(100.0f);
			newBullet->SetDamage(10);

			mpEnemyBullets->push_back(move(newBullet));

			res_ptr<CMissile> newMissile = move(CPool<CMissile>::GetInstance()->GetRes());
			newMissile->SetPosition(GetCenterPoint());
			newMissile->SetRotation(GetRotation());
			newMissile->SetDamage(10);
			newMissile->SetTarget((*mpPlayers)[0]);
			newMissile->SetLists(mpPlayerBullets);

			newBullet.reset(newMissile.release());

			mpEnemyBullets->push_back(move(newBullet));

			mAttackTimer -= kAttackRate;
		}
	}
}

void CEnemyBoss::TakeDamage(int damage)
{
	//Take damage? Potential invulnerable state
	SetHealth( GetHealth() - damage );

	if (GetHealth() < 20)
	{
		mState = State::Overdrive;
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
	SetHealth(100);
	SetRadius(20.0f);
	SetSpeed(20.0f);
	mBobbing = 0.0f;
	mStateTimer = 0.0f;
	mAttackTimer = 0.0f;
	mState = State::Enter;
}