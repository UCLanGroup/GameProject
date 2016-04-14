#include "CBullet.h"
#include "Globals.h"

void CBullet::Init()
{
	if (mInitialized)
		return;
	mInitialized = true;

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

void CBullet::Cleanup()
{
	GetMesh()->RemoveModel(mModel);
	mModel = 0;
}

CBullet::CBullet() : CBaseProjectile()
{

}

CBullet::~CBullet()
{

}