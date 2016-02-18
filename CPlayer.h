#pragma once

#include <TL-Engine.h>
#include "globals.h"
#include "ICollidable.h"
#include "CWeapon.h"

using namespace tle;

class CPlayer : public ICollidable
{
private:
	IMesh* mShieldMesh;
	IMesh* mMesh;
	IModel* mShieldModel;

	int mHealth;
	int mMaxHealth;
	int mShield;
	int mMaxShield;
	float mShieldRegenRate;
	float mRegenTimer;
	float mSpeed; // speed to move plane

	unique_ptr<CWeapon> mWeapon;

public:
	IModel* model;

	void Init();

	void Move(float);

	void TakeDamage(int damage);

	//Sets
	void SetHealth(int health);
	void SetMaxHealth(int health);
	void SetShield(int shield);
	void SetMaxShield(int shield);
	void SetShieldRegen(float regen);

	//Gets
	int GetHealth();
	int GetMaxHealth();
	int GetShield();
	int GetMaxShield();

	CWeapon* GetWeapon();

	//Inherited from ICollidable
	virtual Vector3 GetCenterPoint();
	virtual bool GetMeshAndMatrix(IMesh* mesh, float* matrix);

	~CPlayer();

protected:

};