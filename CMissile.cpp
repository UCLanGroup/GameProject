#define _USE_MATH_DEFINES
#include "CMissile.h"
#include "Globals.h"
#include "CExplosionPool.h"

const float kTurnInterval = 0.5f; //Changes turn direction every 0.5f seconds
const float kTurnSpeed = 90.0f;
const float kMoveSpeed = 50.0f;	//Default move speed
const float kScale = 0.5f;

CMissile::CMissile()
{
	SetMesh(MISSILE_MESH);
	mModel->Scale(kScale);
	//mModel->RotateLocalY(180);

	SetDamage(10);
	SetSpeed(kMoveSpeed);
	SetRadius(2.0f);
	SetDead(false);
}

void CMissile::Update(float delta)
{
	//Move forward
	mModel->MoveLocalZ(GetSpeed() * -delta / kScale);

	//If provided with a target then head towards it
	if (mTarget != 0)
	{
		//Increment timer
		mTimer += delta;
		if (mTimer > kTurnInterval)
		{
			//Calculate the direction towards the target
			Vector3 targetPos = mTarget->GetCenterPoint();
			Vector3 currentPos = GetCenterPoint();

			Vector3 direction = targetPos - currentPos;

			//Get the direction the missile is currently heading in
			float matrix[16];
			mModel->GetMatrix(&(matrix[0]));
			Vector3 forward(matrix[0], matrix[1], matrix[2]);

			//Use dot product to determin direction
			mClockwise = (forward * direction > 0.0f);

			//Reset timer
			mTimer -= kTurnInterval;
		}

		//Turn in the desired direction
		if (!mClockwise)
		{
			mModel->RotateLocalY(kTurnSpeed * delta);
		}
		else
		{
			mModel->RotateLocalY(kTurnSpeed * -delta);
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
			Vector3 loc = (*bullet)->GetCenterPoint();
			CExplosionPool::Instance()->Spawn(loc.GetX(), loc.GetY(), loc.GetZ(), (*bullet)->GetRadius());
			mpPlayerBullets->erase(bullet);

			loc = GetCenterPoint();
			CExplosionPool::Instance()->Spawn(loc.GetX(), loc.GetY(), loc.GetZ(), GetRadius());

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