#pragma once
#define _USE_MATH_DEFINES
#include <IEngine.h>
#include "Globals.h"
#include "CProjectile.h"

using BulletList = std::list<unique_ptr<CProjectile>>;

//Base abstract weapon class
class CWeapon
{
private:
	int mMaxLevel;		//The maximum level
	int mLevel;			//The current level
	int mDamage;		//The damage that projectiles created will inflict
	float mProjSpeed;	//The speed that created projectiles will travel
	float mFireRate;	//The time between shots being fired
	float mRotation;	//The rotational offset from the parent
	float mTimer;		//Keeps track of the time passed since the last shot fired
	bool mIsfiring;		//Whether the weapon is currently firing or not
	CVector3 mOffset;	//The positional offset from the parent
	IEntity* mpTarget;	//The weapon's target, can be nullptr or 0 for no target
	IEntity* mpParent;	//The parent this weapon is attached to
	BulletList* mpProjectiles;	//All projectiles created by the weapon are added to this list

	ISound* mFireSound = 0;

	//Fires the weapon by creating projectiles and adding them to the bullet list
	//If a fire sound is present then the sound is played
	virtual void Fire() = 0;

protected:

	bool mNickMode = false;

	//Factory function allows reuse of code for creating different projectile types based on the weapon's stats
	//Ignore Target: If false (default) it will create the projectile facing the target rather than the
	//the parent's rotation + weapon's rotation offset
	//Needs to be in the header unless you want to get fancy with the includes and stuff
	template<class projectileType>
	projectileType* CreateProjectile(bool ignoreTarget = false);

public:
	//Creates a weapon
	CWeapon(IEntity* parent);

	//Updates the by reloading and/or firing
	void Update(float delta);

	//Increases the weapon's level if not already at the maximum level
	void Upgrade();
	
	//Gets

	//Gets the weapon's maximum level
	int GetMaxLevel();

	//Gets the weapon's current level
	int GetLevel();

	//Gets the weapon's damage
	int GetDamage();

	//Gets the weapon's projectile speed
	float GetProjSpeed();

	//Gets the rotational offset
	float GetRotation();

	//Gets the weapon's fire rate
	float GetFireRate();

	//Returns whether the weapon is firing or not
	bool IsFiring();

	//Gets the positional offset from the weapon's parent
	CVector3& GetPosOffset();

	//Gets the entity that the weapon is equiped to
	IEntity* GetParent();

	//Gets the entity that the weapon is targetting
	//If there is no target then zero is returned
	IEntity* GetTarget();

	//Gets the bullet list that projectiles created by the weapon are added to
	BulletList* GetBulletList();

	//Gets the sound that is played when the weapon fires
	//If the weapon has no sound then zero is returned
	ISound* GetFireSound();

	//Sets

	//Sets the weapon's maximum level
	void SetMaxLevel(int level);

	//Sets the weapon's current level, this is capped at the weapon's max level
	void SetLevel(int level);

	//Sets the damage
	void SetDamage(int damage);

	//Sets the projectile of created projectiles
	void SetProjSpeed(float projSpeed);

	//Set the rotational offset
	void SetRotation(float rotation);

	//Sets the reload time between shots
	void SetFireRate(float fireRate);

	//Sets whether the weapon is firing
	virtual void SetFiring(bool isFiring);

	//Sets the positional offset from the parent
	void SetPosOffset(const CVector3& pos);

	//Sets the weapon's parent
	void SetParent(IEntity* pParent);

	//Sets the target that the weapon will fire at
	//If no target then the weapon will fire forward
	void SetTarget(IEntity* pTarget);

	//Sets the projectile list that projectiles created by the weapon are added to
	void SetBulletList(BulletList* pBulletList);

	//Sets the sound that is played when the weapon fires
	void SetFireSound(ISound* fireSound);

	//Nick Cage mode
	void ActivateTheCage();

	//Destroys stuff
	virtual ~CWeapon();
};

//Factory function allows reuse of code for creating different projectile types based on the weapon's stats
//Needs to be in the header unless you want to get fancy with the includes and stuff
template<class projectileType>
projectileType* CWeapon::CreateProjectile(bool ignoreTarget)
{
	CVector3 parentPos = GetParent()->GetCenterPoint();

	projectileType* bullet = new projectileType();

	bullet->SetPosition(parentPos);
	bullet->SetRotation(mpParent->GetRotation());
	bullet->GetModel()->MoveLocal(mOffset.x, mOffset.y, mOffset.z);

	//If there's a target then fire directly at the target
	if (GetTarget() && !ignoreTarget)
	{
		CVector3 targetPos = GetTarget()->GetCenterPoint();

		CVector3 dif = targetPos - parentPos;

		//Calculate the bearing from north
		float rotation = 90.0f - atan2f(dif.z, dif.x) * (180.0f / static_cast<float>(M_PI));

		bullet->SetRotation(rotation);
	}
	else //Otherwise fire with the weapon's rotational offset
	{
		bullet->GetModel()->RotateY(mRotation);
	}

	bullet->SetDamage(mDamage);
	bullet->SetSpeed(mProjSpeed);
	bullet->SetParent(mpParent);
	bullet->SetExplodeable(true);

	if (mNickMode) bullet->ActivateTheCage();

	return bullet;
}