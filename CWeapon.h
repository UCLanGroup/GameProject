#pragma once
#include "Globals.h"
#include <IEngine.h>
#include "CBaseProjectile.h"

using BulletList = std::list<unique_ptr<CBaseProjectile>>;

class CWeapon
{
private:
	int mMaxLevel;
	int mLevel;
	int mDamage;
	float mProjSpeed;
	float mFireRate;
	float mTimer;
	bool mIsfiring;
	IEntity* mpParent;
	IEntity* mpTarget;
	BulletList* mpProjectiles;

	sf::Sound mFireSound;

public:

	// Moved to allow access from network
	virtual void Fire() = 0;

	CWeapon(IEntity* parent);

	void Update(float delta);
	void Upgrade();
	
	//Gets

	int GetMaxLevel();
	int GetLevel();
	int GetDamage();
	float GetProjSpeed();
	float GetFireRate();
	float GetTimer();
	bool IsFiring();
	IEntity* GetParent();
	IEntity* GetTarget();
	BulletList* GetBulletList();

	//Sets

	void SetMaxLevel(int level);
	void SetLevel(int level);
	void SetDamage(int damage);
	void SetProjSpeed(float projSpeed);
	void SetFireRate(float fireRate);
	void SetTimer(float time);
	virtual void SetFiring(bool isFiring);
	void SetParent(IEntity* pParent);
	void SetTarget(IEntity* pTarget);
	void SetBulletList(BulletList* pBulletList);
	void SetFireSound(const sf::SoundBuffer &soundBuffer);

	virtual ~CWeapon();
};