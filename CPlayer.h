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
	const float kInvulTextureRate = 0.05f;
	const bool kCheatMode = true;

	IMesh* mShieldMesh;
	IMesh* mProjectileMesh;
	IModel* mShieldModel;

	int mScore;

	int mHealth;
	int mLives;
	int mMaxHealth;
	int mShield;
	int mMaxShield;
	int mInvulTexture;
	float mShieldRegenRate;
	float mRegenTimer;
	float mInvulTimer;
	float mInvulTextureTimer;
	float mSpeed; // speed to move plane
	float mWeaponPowerupTimer = 0.0f;
	float mRotation = 0.0f;

	bool mInvulTextureAccending = false;

	unique_ptr<CWeapon> mMainWeapon;
	unique_ptr<CWeapon> mBonusWeapon;

	BulletList* mpPlayerBullets = 0;
	BulletList* mpEnemyBullets = 0;

public:
	void Init();
	void Cleanup();

	//Moves and updates the player
	void Move(float);

	//Checks the collision between the player and enemy projectiles
	virtual void CheckCollision();

	//The player takes damage to the shield or health is there is no shield
	//Sets dead flag if it kills the player
	void TakeDamage(int damage);

	//Makes the player invulnerable for a specific duration
	void MakeInvulnerable(float time);

	//Increases the player's score
	//Pass a negative to decrease the score
	void IncreaseScore(int value);

	//Removes a life from the player and handles death
	void LoseLife();

	//Gives the player and extra life
	void GainLife();

	//Upgrades the mmain weapon
	void UpgradeWeapon();

	//Sets
	void SetScore(int score);
	void SetLives(int lives);
	void SetHealth(int health);
	void SetMaxHealth(int health);
	void SetShield(int shield);
	void SetMaxShield(int shield);
	void SetShieldRegen(float regen);

	//Sets the main weapon that the player uses at all times
	void SetMainWeapon(CWeapon* weapon);

	//Sets the bonus weapon of the player, the bonus weapon lasts for a set duration
	//While active the bonus weapon will be used instead of the main weapon
	void SetBonusWeapon(CWeapon* weapon, float duration);

	void SetLists(BulletList* playerBullets, BulletList* enemyBullets);

	//Gets
	int GetScore();
	int GetLives();
	int GetHealth();
	int GetMaxHealth();
	int GetShield();
	int GetMaxShield();

	//Returns a pointer to the main weapon
	CWeapon* GetMainWeapon();

	//Inherited from IEntity
	virtual void Reset();

	//Ensures all player models are destroyed (calls Cleanup())
	~CPlayer();

protected:

};