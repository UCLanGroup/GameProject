#pragma once
#include "Globals.h"
#include <IEngine.h>
#include "CProjectile.h"

using BulletList = std::list<unique_ptr<CProjectile>>;

class CWeapon
{
private:
	int mDamage;
	float mProjSpeed;
	float mFireRate;
	float mTimer;
	bool mIsfiring;
	IEntity* mpParent;
	IEntity* mpTarget;
	BulletList* mpProjectiles;

	virtual CProjectile* Fire() = 0;

public:
	CWeapon(IEntity* parent);

	void Update(float delta);
	
	//Gets

	int GetDamage();
	float GetProjSpeed();
	float GetFireRate();
	float GetTimer();
	bool IsFiring();
	IEntity* GetParent();
	IEntity* GetTarget();
	BulletList* GetBulletList();

	//Sets

	void SetDamage(int damage);
	void SetProjSpeed(float projSpeed);
	void SetFireRate(float fireRate);
	void SetTimer(float time);
	void SetFiring(bool isFiring);
	void SetParent(IEntity* pParent);
	void SetTarget(IEntity* pTarget);
	void SetBulletList(BulletList* pBulletList);
};