#include "CBaseProjectile.h"
#include "Globals.h"

CBaseProjectile::CBaseProjectile()
{
}

void CBaseProjectile::Update(float delta)
{
	mModel->MoveLocalZ(delta * (mSpeed * 4.0f));
}

void CBaseProjectile::CheckCollision()
{
	//No collision check atm
}

//Gets

int CBaseProjectile::GetDamage()
{
	return mDamage;
}

float CBaseProjectile::GetSpeed()
{
	return mSpeed;
}

IEntity* CBaseProjectile::GetParent()
{
	return mParent;
}

//Sets

void CBaseProjectile::SetDamage(int damage)
{
	mDamage = damage;
}

void CBaseProjectile::SetSpeed(float speed)
{
	mSpeed = speed;
}

void CBaseProjectile::SetMatrix(float* matrix)
{
	mModel->SetMatrix(matrix);
	mModel->ResetScale();
	mModel->Scale(mScale);
}

void CBaseProjectile::SetParent(IEntity* parent)
{
	mParent = parent;
}

//Inherited from IEntity : IResource

void CBaseProjectile::Reset()
{
	//Empty
	SetDead(false);
}

CBaseProjectile::~CBaseProjectile()
{
	//Model destruction is handled by IEntity destructor
}