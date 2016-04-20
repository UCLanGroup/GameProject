#pragma once
#include "Globals.h"
#include "IEntity.h"
#include "CWeapon.h"

using namespace tle;

class CPlayer : public IEntity
{
private:
	const float kMaxLean = 30.0f;			//The maximum the player can lean to the side
	const float kRotateSpeed = 150.0f;		//The turn speed in degrees for leaning sideways
	const float kInvulTextureRate = 0.05f;	//The rate at which invul textures are animated
	const float kShieldRegenRate = 0.25f;	//The rate at which shield health regens
	const int kMaxLives = 8;
	const bool kCheatMode = true;			//gg wp

	bool mInitialised = false;	//Stores whether the player has been initialised

	IMesh* mShieldMesh;		//Mesh for the shield
	IModel* mShieldModel;	//Shield model, will be either hidden or attached to mModel

	int mLives;	//The number of *extra* lives the player has remaining
	int mScore; //The score from destroying stuff

	int mMaxHealth;		//The maximum amount of health
	int mHealth;		//The current health amount. 0 <= mShield <= mMaxShield 
	int mMaxShield;		//The maximum amount of shield
	int mShield;		//The current shield amount. 0 <= mShield <= mMaxShield 
	float mSpeed;		//Speed to move plane
	float mRotation;	//The current lean rotation

	float mRegenTimer;					//The amount of time needing to pass without being hit before shield regen starts
	float mInvulTimer;					//The amount of time left for invulnerability
	float mInvulTextureTimer;			//The amount of time until the next invul texture
	float mWeaponPowerupTimer;			//The amount of time left before the bonus weapon is destroyed

	int mInvulTexture;					//The current invul texture
	bool mInvulTextureAccending = false;//The direction the invul textures are being iterated through

	unique_ptr<CWeapon> mMainWeapon;	//Main weapon which upgrades are applied to
	unique_ptr<CWeapon> mBonusWeapon;	//Temporary super weapon

	BulletList* mpPlayerBullets = 0;
	BulletList* mpEnemyBullets = 0;

public:
	//Initial set up
	//It is not safe to use other player functions until Init is called
	void Init();

	//Removes all models and sprites
	//It is not safe to use other player functions after Cleanup until Init is called again
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

	//Upgrades the main weapon
	void UpgradeWeapon();

	//Sets

	//Sets the score
	void SetScore(int score);

	//Sets the number of extra lives the player has
	void SetLives(int lives);

	//Sets the health, this is capped at the player's max health
	void SetHealth(int health);

	//Sets the maximum health amount
	void SetMaxHealth(int health);

	//Sets the shield, this is capped at the player's max shield
	void SetShield(int shield);

	//Sets the maximum shield amount
	void SetMaxShield(int shield);

	//Sets the main weapon that the player uses at all times
	void SetMainWeapon(CWeapon* weapon);

	//Sets the bonus weapon of the player, the bonus weapon lasts for a set duration
	//While active the bonus weapon will be used instead of the main weapon
	void SetBonusWeapon(CWeapon* weapon, float duration);

	//Gives the player access to the player and enemy bullet lists
	void SetLists(BulletList* playerBullets, BulletList* enemyBullets);

	//Gets

	//Returns the player's score
	int GetScore();

	//Returns the number of extra lives remaining
	int GetLives();

	//Returns the current health
	int GetHealth();

	//Returns the maximum amount of health
	int GetMaxHealth();

	//Returns the current shield
	int GetShield();

	//Returns the maximum amount of shield
	int GetMaxShield();

	//Returns a pointer to the main weapon
	CWeapon* GetMainWeapon();

	//Inherited from IEntity
	virtual void Reset();

	//Ensures all player models are destroyed (calls Cleanup())
	~CPlayer();

protected:

};