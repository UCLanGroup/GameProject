#include "CLaser.h"
#include "CProjectile.h"
#include "CMatrix4x4.h"

//class CLaser : public CWeapon
//{
//private:
//	IModel* mpLaserModel;
//
//	virtual void Fire();
//
//public:
//	CLaser(IEntity* parent, int damage, float fireRate);
//
//	virtual void SetFiring(bool isFiring);
//
//	virtual ~CLaser();
//};

CLaser::CLaser(IEntity* parent, int damage, float fireRate) : CWeapon(parent)
{
	SetDamage(damage);
	SetFireRate(fireRate);
	SetProjSpeed(10000.0f);
	mpBeamMesh = gEngine->LoadMesh(PARTICLE_MODEL);
	mpLaserModel = 0;
}

void CLaser::Fire()
{
	tlx::CMatrix4x4 matrix;
	GetParent()->GetMatrix(matrix.m);
	CVector3 direction(matrix.m[8], matrix.m[9], matrix.m[10]);
	CVector3 pos(matrix.m[12], matrix.m[13] - 500.0f, matrix.m[14]);

	direction *= 4.0f;

	for (int i = 0; i < 25; i++)
	{
		CProjectile* bullet = new CProjectile();

		bullet->SetPosition(pos);
		bullet->SetDamage(GetDamage());
		bullet->SetSpeed(GetProjSpeed());
		bullet->SetParent(GetParent());

		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));

		pos += direction;
	}

}

void CLaser::SetFiring(bool isFiring)
{
	if (isFiring != IsFiring())
	{
		//State has changed

		if (isFiring)
		{
			//Now firing, so add laser beam
			mpLaserModel = gEngine->GetModel(mpBeamMesh, LASER_BEAM_TEX);
			mpLaserModel->SetPosition(0.5f, 0.0f, 100.0f);
			mpLaserModel->AttachToParent(GetParent()->GetModel());
			mpLaserModel->ResetScale();
			mpLaserModel->ScaleZ(100.0f);
			mpLaserModel->ScaleX(3.0f);
		}
		else if(mpLaserModel)
		{
			//No longer firing, remove laser beam
			mpLaserModel->DetachFromParent();
			gEngine->CacheModel(mpLaserModel, LASER_BEAM_TEX);
			mpLaserModel = 0;
		}
	}
	CWeapon::SetFiring(isFiring);
}

CLaser::~CLaser()
{
	if (mpLaserModel)
	{
		mpLaserModel->DetachFromParent();
		gEngine->CacheModel(mpLaserModel, LASER_BEAM_TEX);
		mpLaserModel = 0;
	}
}