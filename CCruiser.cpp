#define _USE_MATH_DEFINES
#include "CCruiser.h"
#include "CPlayer.h"
#include <iostream>

const float kRotateSpeed = 40.0f;
const float kRotorSpeed = 720.0f; //Rotation Speed
const float kFireDuration = 1.5f;
const float kRotationMargin = 2.5f;

CCruiser::CCruiser(std::vector<CPlayer*>* players, BulletList* playerBullets, BulletList* enemyBullets) : CEnemy(players, playerBullets, enemyBullets)
{
	SetMesh(HAVOC_BOSS_MESH);

	//Ensure model is reset in the case it reuses a cached model
	mModel->ResetScale();
	mModel->ResetOrientation();

	mModel->RotateY(180.0f);

	mWeapon.reset(new CMissileBarrage(this, 10, 75.0f, 0.1f));
	mWeapon->SetBulletList(enemyBullets);
	mWeapon->SetEnemyBulletList(playerBullets);
	mWeapon->SetFiring(false);

	/*if (static_cast<int>(players->size()) > 0)
	{
		mWeapon->SetTarget((*players)[0]);
	}*/

	SetHealth(25);
	SetRadius(10.0f);
	SetValue(50);
	SetSpeed(30.0f);
	mStateTimer = 0.0f;
	mState = State::Enter;
}

void CCruiser::Move(float delta)
{
	switch (mState)
	{
	case State::Enter:
		//Move downwards
		mModel->MoveZ(GetSpeed() * -delta);

		if (AREA_BOUNDS_TOP - (2.0f * GetRadius()) > mModel->GetZ())
		{
			mState = State::Rotate;
		}
		break;
	case State::Attack:
		break;
	case State::Rotate:
	{
		RotateTowards((*mpPlayers)[0]->GetCenterPoint(), delta * kRotateSpeed);

		float bearingToTarget = BearingTowards((*mpPlayers)[0]->GetCenterPoint());
		float rotation = GetRotation();

		float rotDif = bearingToTarget > rotation ? bearingToTarget - rotation : rotation - bearingToTarget;

		if (rotDif < kRotationMargin)
		{
			mState = State::Attack;
			mWeapon->SetFiring(true);
			mStateTimer = 0.0f;
		}
	}
		break;
	default:
		break;
	}
}

void CCruiser::Update(float delta)
{
	mStateTimer += delta;
	(mModel->GetNode(6))->RotateY(delta * kRotorSpeed); //Rotate spinny thing

	mWeapon->Update(delta);

	Move(delta);

	switch (mState)
	{
	case State::Enter:
		break;
	case State::Attack:
		if (mStateTimer > kFireDuration)
		{
			mState = State::Rotate;
			mWeapon->SetFiring(false);
		}
		break;
	case State::Rotate:
		break;
	default:
		break;
	}
}

void CCruiser::Reset()
{

}