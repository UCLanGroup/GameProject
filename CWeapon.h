#pragma once
#include "Globals.h"
#include <list>
#include <TL-Engine.h>
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
	tle::IModel* mParent;
	tle::IMesh* mProjMesh;

public:
	CWeapon(tle::IModel* parent, tle::IMesh* mesh, int damage, float projSpeed, float fireRate);

	void Update(float delta, BulletList& projectiles);
	
	//Gets

	int GetDamage();
	float GetProjSpeed();
	float GetFireRate();
	float GetTimer();
	IModel* GetParent();
	IMesh* GetProjMesh();

	//Sets

	void SetDamage(int damage);
	void SetProjSpeed(float projSpeed);
	void SetFireRate(float fireRate);
	void SetTimer(float time);
	void SetParent(IModel* parent);
	void SetProjMesh(IMesh* projMesh);
};