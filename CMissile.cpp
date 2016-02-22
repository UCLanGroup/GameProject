#define _USE_MATH_DEFINES
#include "CMissile.h"
#include "Globals.h"
#include "CExplosionPool.h"

const float kTurnInterval = 0.5f; //Changes turn direction every 0.5f seconds
const float kTurnSpeed = 90.0f;
const float kMoveSpeed = 50.0f;	//Default move speed

CMissile::CMissile()
{
	SetMesh(MISSILE_MESH);

	SetDamage(10);
	SetSpeed(kMoveSpeed);
	SetRadius(2.0f);
}

void CMissile::Update(float delta)
{
	mModel->MoveLocalZ(GetSpeed() * delta);
	if (mTarget != 0)
	{
		Vector3 targetPos = mTarget->GetCenterPoint();
		Vector3 currentPos = GetCenterPoint();

		Vector3 direction = targetPos - currentPos;

		mTimer += delta;
		if (mTimer > kTurnInterval)
		{
			float matrix[16];
			mModel->GetMatrix(&(matrix[0]));
			Vector3 forward(matrix[0], matrix[1], matrix[2]);

			mClockwise = (forward * direction > 0.0f);

			mTimer -= kTurnInterval;
		}
		if (mClockwise)
		{
			mModel->RotateY(kTurnSpeed * delta);
		}
		else
		{
			mModel->RotateY(-kTurnSpeed * delta);
		}
	}
}

void CMissile::CheckCollision()
{
	if (mpPlayerBullets == 0) return;

	auto bullet = mpPlayerBullets->begin();

	while (bullet != mpPlayerBullets->end())
	{
		if (CollidesMesh(bullet->get()))
		{
			CExplosionPool::Instance()->Spawn((*bullet)->GetCenterPoint().GetX(), 0.0f, (*bullet)->GetCenterPoint().GetZ(), (*bullet)->GetRadius());
			bullet = mpPlayerBullets->erase(bullet);

			Vector3 loc = GetCenterPoint();
			CExplosionPool::Instance()->Spawn(loc.GetX(), loc.GetY(), loc.GetZ(), GetRadius());

			SetDead(true);
			//Don't collide with any of the remaining bullets when dead
			return;
		}
	}
}

void CMissile::SetTarget(IEntity* target)
{
	mTarget = target;
}

void CMissile::SetRotation(float rotation)
{
	mRotation = rotation;
}

void CMissile::SetLists(std::list<res_ptr<CProjectile>>* playerBullets)
{
	mpPlayerBullets = playerBullets;
}


IEntity* CMissile::GetTarget()
{
	return mTarget;
}

float CMissile::GetRotation()
{
	return mRotation;
}

bool CMissile::IsClockwise()
{
	return mClockwise;
}

void CMissile::Reset()
{

}