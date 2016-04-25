#include "CProjectile.h"
#include "Globals.h"

CProjectile::CProjectile()
{
	SetMesh(BULLET_MESH);
	//mModel->SetMatrix(matrix);
	mModel->ResetScale();
	mModel->Scale(mScale);

	mDamage = 1;
	mSpeed = 50.0f;
	mParent = 0;
	SetRadius(2.0f);
	SetDead(false);
}

void CProjectile::Update(float delta)
{
	mModel->MoveLocalZ(delta * (mSpeed * 4.0f));
}

void CProjectile::CheckCollision()
{
	//No collision check atm
}

//Gets

int CProjectile::GetDamage()
{
	return mDamage;
}

float CProjectile::GetSpeed()
{
	return mSpeed;
}

IEntity* CProjectile::GetParent()
{
	return mParent;
}

//Sets

void CProjectile::SetDamage(int damage)
{
	mDamage = damage;
}

void CProjectile::SetSpeed(float speed)
{
	mSpeed = speed;
}

void CProjectile::SetMatrix(float* matrix)
{
	mModel->SetMatrix(matrix);
	mModel->ResetScale();
	mModel->Scale(mScale);
}

void CProjectile::SetParent(IEntity* parent)
{
	mParent = parent;
}

//Inherited from IEntity : IResource

void CProjectile::Reset()
{
	//Empty
	SetDead(false);
}

//Nick Cage mode
void CProjectile::ActivateTheCage()
{
	//Do nothing by default
}

CProjectile::~CProjectile()
{
	//Model destruction is handled by IEntity destructor
}