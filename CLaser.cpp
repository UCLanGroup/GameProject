#include "CLaser.h"
#include "CProjectile.h"
#include "CMatrix4x4.h"

CLaser::CLaser(IEntity* parent, int damage, float fireRate) : CWeapon(parent)
{
	SetDamage(damage);
	SetFireRate(fireRate);
	SetProjSpeed(1000000.0f); //This is so that the projectile are instantly off screen the frame after being fired
	mpBeamMesh = gEngine->LoadMesh(PARTICLE_MODEL);
	mpLaserModel = 0;
}

void CLaser::Fire()
{
	//Get matrix for current player location and forward vector
	tlx::CMatrix4x4 matrix;
	GetParent()->GetMatrix(matrix.m);

	//Create forward vector (z axis)
	CVector3 direction(matrix.m[8], matrix.m[9], matrix.m[10]);

	//Get position from matrix
	//Since we've already got the matrix it's slightly more efficient than calling GetParent()->GetCenterPoint()
	CVector3 pos(matrix.m[12], OFF_SCREEN_Y, matrix.m[14]);

	//Calculate the rotation of the parent entity, just so it only needs to be calculated once
	float rotation = GetParent()->GetRotation();

	//Makes the space between invisible bullets 4.0f instead of 1.0f
	direction *= 4.0f;

	for (int i = 0; i < 35; i++)
	{
		CProjectile* bullet = new CProjectile();

		bullet->SetPosition(pos);
		bullet->SetRotation(rotation);

		bullet->SetDamage(GetDamage());
		bullet->SetSpeed(GetProjSpeed());
		bullet->SetParent(GetParent());
		bullet->SetExplodeable(false);

		GetBulletList()->push_back(unique_ptr<CProjectile>(bullet));

		//Increment position of next bullet
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
			mpLaserModel->SetPosition(0.5f, 0.0f, 50.0f);
			mpLaserModel->AttachToParent(GetParent()->GetModel());

			//Attaching to parent can screw over the scaling, so reset scale
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
		//Remove the laser model and cache it
		mpLaserModel->DetachFromParent();
		gEngine->CacheModel(mpLaserModel, LASER_BEAM_TEX);
		mpLaserModel = 0;
	}
}