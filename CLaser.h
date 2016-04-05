#pragma once
#include "CWeapon.h"

class CLaser : public CWeapon
{
private:
	IModel* mpLaserModel;
	IMesh* mpBeamMesh;

	virtual void Fire();

public:
	CLaser(IEntity* parent, int damage, float fireRate);

	virtual void SetFiring(bool isFiring);

	virtual ~CLaser();
};