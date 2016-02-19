#define _USE_MATH_DEFINES
#include "CEnemyBoss.h"
#include "CMeshCache.h"
#include "CPlayState.h"
#include <iostream>


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

		//Avoid player 1, don't give a crap about the weakling player 2

		CPlayer* player = CPlayState::Instance()->GetPlayer1();
		Vector3 locDif = player->GetCenterPoint() - GetCenterPoint();

		if (abs(locDif.GetX()) < GetRadius()) //Check if player is below
		{
			if (locDif.GetX() > 0.0f) //Dodge left
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
	(mModel->GetNode(6))->RotateY(delta * 720.0f); //Rotate spinny thing

	if (mState == State::Attack1)
	{
		//Basic attack pattern, switches to attack2 after set amount of time
	}
	else if (mState == State::Attack2)
	{
		//Basic attack pattern, switches to attack1 after set amount of time
	}
	else if (mState == State::Overdrive)
	{
		//Death, enters overdrive when low on health
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
	mState = State::Enter;
}