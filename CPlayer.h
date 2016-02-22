#pragma once

#include <TL-Engine.h>
#include "globals.h"
#include "IEntity.h"
#include "CWeapon.h"

using namespace tle;

class CPlayer : public IEntity
{
private:
	IMesh* mShieldMesh;
	IMesh* mProjectileMesh;
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
	void Init();
	void Cleanup();

	void Move(float);
	virtual void CheckCollision();

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

	//Inherited from IEntity
	virtual void Reset();

	~CPlayer();

protected:

};