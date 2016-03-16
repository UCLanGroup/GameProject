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
	IEntity* mParent;
	tle::IMesh* mProjMesh;

public:
	CWeapon(IEntity* parent, tle::IMesh* projectileMesh, int damage, float projSpeed, float fireRate);

	void Update(float delta, BulletList& projectiles);
	
	//Gets

	int GetDamage();
	float GetProjSpeed();
	float GetFireRate();
	float GetTimer();
	IEntity* GetParent();
	IMesh* GetProjMesh();

	//Sets

	void SetDamage(int damage);
	void SetProjSpeed(float projSpeed);
	void SetFireRate(float fireRate);
	void SetTimer(float time);
	void SetParent(IEntity* parent);
	void SetProjMesh(IMesh* projMesh);
};