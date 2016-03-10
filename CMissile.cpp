#define _USE_MATH_DEFINES
#include "CMissile.h"
#include "Globals.h"
#include "CExplosionPool.h"
#include <iostream>

const float kTurnInterval = 0.5f; //Changes turn direction every 0.5f seconds
const float kTurnSpeed = 90.0f;
const float kMoveSpeed = 50.0f;	//Default move speed

CMissile::CMissile()
{
	SetMesh(MISSILE_MESH);

	SetDamage(10);
	SetSpeed(kMoveSpeed);
	SetRadius(2.0f);
	SetDead(false);

	mTimer = kTurnInterval;
	mEmitter = gEngine->CreateEmitter(EEmissionType::Line, "Smoke1.png", 0.025f);
	mEmitter->SetParticleLife(0.5f);
	mEmitter->SetParticleScale(2.0f);
	mEmitter->AttachToParent(mModel);
	mEmitter->Start();
}

void CMissile::Update(float delta)
{
	//Move forward
	mModel->MoveLocalZ(GetSpeed() * delta);

	//If provided with a target then head towards it
	if (mTarget != 0)
	{
		//Increment timer
		mTimer += delta;
		if (mTimer > kTurnInterval)
		{
			//Calculate the direction towards the target
			CVector3 targetPos = mTarget->GetCenterPoint();
			CVector3 currentPos = GetCenterPoint();

			CVector3 direction = targetPos - currentPos;

			//Get the direction the missile is currently heading in
			float matrix[16];
			mModel->GetMatrix(&(matrix[0]));
			CVector3 forward(matrix[0], matrix[1], matrix[2]);

			//Use dot product to determin direction
			mClockwise = (Dot(forward, direction) > 0.0f);

			//Reset timer
			mTimer -= kTurnInterval;
		}

		//Turn in the desired direction
		if (!mClockwise)
		{
			mModel->RotateLocalY(kTurnSpeed * -delta);
		}
		else
		{
			mModel->RotateLocalY(kTurnSpeed * delta);
		}
	}
}

void CMissile::CheckCollision()
{
	//Check if given anything to collide against
	if (mpPlayerBullets == 0) return;

	auto bullet = mpPlayerBullets->begin();

	while (bullet != mpPlayerBullets->end())
	{
		if (CollidesSphere(bullet->get()))
		{
			//Upon collision with player's bullet destroy self and the bullet
			//Explosions!
			CVector3 loc = (*bullet)->GetCenterPoint();
			CExplosionPool::Instance()->Spawn(loc.x, loc.y, loc.z, (*bullet)->GetRadius());
			mpPlayerBullets->erase(bullet);

			loc = GetCenterPoint();
			CExplosionPool::Instance()->Spawn(loc.x, loc.y, loc.z, GetRadius());

			SetDead(true);
			//Don't collide with any of the remaining bullets when dead
			return;
		}
		else
		{
			bullet++;
		}
	}
}

void CMissile::SetTarget(IEntity* target)
{
	mTarget = target;
}

void CMissile::SetLists(std::list<res_ptr<CProjectile>>* playerBullets)
{
	mpPlayerBullets = playerBullets;
}


IEntity* CMissile::GetTarget()
{
	return mTarget;
}

bool CMissile::IsClockwise()
{
	return mClockwise;
}

void CMissile::Reset()
{
	SetDead(false);
}

CMissile::~CMissile()
{
	mEmitter->DetachFromParent();
	mEmitter->Stop();
	gEngine->RemoveEmitter(mEmitter);
}