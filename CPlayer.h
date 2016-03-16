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

	const int mStartBarPosX = 90;
	const int mStartBarPosY = 936;
	float mShieldMove = 0;
	float mHealthMove = 0;

	unique_ptr<CWeapon> mWeapon;

	vector<ISprite*> mLifeSprites;
	ISprite* mpHealthBar;
	ISprite* mpShieldBar;

	IFont* mFont;

	BulletList* mpPlayerBullets = 0;
	BulletList* mpEnemyBullets = 0;

public:
	void Init();
	void Cleanup();

	void Move(float);
	virtual void CheckCollision();

	void TakeDamage(int damage);
	void IncreaseScore(int value);

	void DrawText();
	void AnimateHealth(float delta);
	void AnimateShield(float delta);

	//Sets
	void SetScore(int score);
	void SetHealth(int health);
	void SetMaxHealth(int health);
	void SetShield(int shield);
	void SetMaxShield(int shield);
	void SetShieldRegen(float regen);

	void SetLists(BulletList* playerBullets, BulletList* enemyBullets);

	//Gets
	int GetScore();
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