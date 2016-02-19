#pragma once
#include "Globals.h"
#include "Vector3.h"
#include "CWeapon.h"
#include "IEntity.h"

using Path = std::vector<Vector3>;

class CEnemy : public IEntity
{
protected:
	//Stats
	int mHealth;
	float mSpeed;
	std::vector<CWeapon> mWeapons;
	int mValue;

	//Pathing
	Path* mpPath;
	Vector3 mOffset;
	int mPathPos;
	float mMoveTimer;
	bool mFinished;

public:
	CEnemy();
	CEnemy(Path* path, Vector3& offset);

	//Updates
	virtual void Move(float delta);
	virtual void Update(float delta);
	virtual void TakeDamage(int damage);
	virtual bool CheckCollision();

	//Sets
	void SetHealth(int health);
	void SetSpeed(float speed);
	void AddWeapon(CWeapon w);
	void SetValue(int value);
	void SetPath(Path* path, Vector3& offset);

	//Gets
	int GetHealth();
	float GetSpeed();
	std::vector<CWeapon>* GetWeapons();
	int GetValue();
	bool IsFinished();

	//Inherited from IEntity : IResource
	virtual void Reset();

	~CEnemy();
};