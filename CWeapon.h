#pragma once
#include "Globals.h"
#include <list>
#include <IEngine.h>
#include "CProjectile.h"
#include "CPool.h"

using BulletList = std::list<res_ptr<CProjectile>>;

class CWeapon
{
private:
	int mDamage;
	float mProjSpeed;
	float mFireRate;
	float mTimer;
	bool mIsfiring;
	IEntity* mpParent;
	tle::IMesh* mpProjMesh;
	BulletList* mpProjectiles;

public:
	CWeapon(IEntity* parent, tle::IMesh* projectileMesh, int damage, float projSpeed, float fireRate);

	void Update(float delta);
	
	//Gets

	int GetDamage();
	float GetProjSpeed();
	float GetFireRate();
	float GetTimer();
	bool IsFiring();
	IEntity* GetParent();
	IMesh* GetProjMesh();
	BulletList* GetBulletList();

	//Sets

	void SetDamage(int damage);
	void SetProjSpeed(float projSpeed);
	void SetFireRate(float fireRate);
	void SetTimer(float time);
	void SetFiring(bool isFiring);
	void SetParent(IEntity* pParent);
	void SetProjMesh(IMesh* pProjMesh);
	void SetBulletList(BulletList* pBulletList);
};