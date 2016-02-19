#define _USE_MATH_DEFINES
#include "CMissile.h"
#include "Globals.h"
#include "CExplosionPool.h"

CMissile::CMissile()
{
	SetMesh(BULLET_MESH);

	SetDamage(10);
	SetSpeed(20.0f);
	SetRadius(2.0f);
}

void CMissile::Update(float delta)
{
	if (mTarget != 0)
	{
		Vector3 targetPos = mTarget->GetCenterPoint();
		Vector3 currnetPos = GetCenterPoint();
		//Calculate bearing from north
		float xDif = targetPos.GetX() - mModel->GetX();
		float zDif = targetPos.GetZ() - mModel->GetZ();
		float angle = 90.0f - atan2f(zDif, xDif) * (180.0f / static_cast<float>(M_PI));

		//Reset orientation then apply new angle
		mModel->ResetOrientation();
		mModel->RotateY(angle);
	}
	mModel->MoveLocalZ(GetSpeed() * delta);
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

void CMissile::SetLists(std::list<res_ptr<CProjectile>>* playerBullets)
{
	mpPlayerBullets = playerBullets;
}

void CMissile::Reset()
{

}