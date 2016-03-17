#pragma once
#include "Globals.h"
#include "IEntity.h"
#include "CWeapon.h"

using namespace tle;

class CPlayer : public IEntity
{
private:
	const float kMaxLean = 30.0f;
	const float kRotateSpeed = 150.0f;

	IMesh* mShieldMesh;
	IMesh* mProjectileMesh;
	IModel* mShieldModel;

	int mScore;

	int mHealth;
	int mLives;
	int mMaxHealth;
	int mShield;
	int mMaxShield;
	float mShieldRegenRate;
	float mRegenTimer;
	float mSpeed; // speed to move plane

	float mRotation = 0.0f;

	unique_ptr<CWeapon> mWeapon;

	BulletList* mpPlayerBullets = 0;
	BulletList* mpEnemyBullets = 0;

public:
	void Init();
	void Cleanup();

	void Move(float);
	virtual void CheckCollision();

	void TakeDamage(int damage);
	void IncreaseScore(int value);
	void LoseLife();
	void GainLife();

	//Sets
	void SetScore(int score);
	void SetLives(int lives);
	void SetHealth(int health);
	void SetMaxHealth(int health);
	void SetShield(int shield);
	void SetMaxShield(int shield);
	void SetShieldRegen(float regen);

	void SetLists(BulletList* playerBullets, BulletList* enemyBullets);

	//Gets
	int GetScore();
	int GetLives();
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