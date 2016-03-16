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
	int mScore;
	int mLives;
	int mMaxHealth;
	int mShield;
	int mMaxShield;
	float mShieldRegenRate;
	float mRegenTimer;
	float mSpeed; // speed to move plane

	float mRotation = 0.0f;

	unique_ptr<CWeapon> mWeapon;

	vector<ISprite*> mLifeSprites;

	IFont* mFont;

public:
	void Init();
	void Cleanup();

	void Move(float);
	virtual void CheckCollision();

	void TakeDamage(int damage);
	void IncreaseScore(int value);

	void DrawText();

	//Sets
	void SetScore(int score);
	void SetHealth(int health);
	void SetMaxHealth(int health);
	void SetShield(int shield);
	void SetMaxShield(int shield);
	void SetShieldRegen(float regen);

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