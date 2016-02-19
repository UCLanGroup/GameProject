#pragma once
#include "Globals.h"
#include "Vector3.h"
#include "CWeapon.h"
#include "IEntity.h"
#include "CPool.h"
#include <list>

//Forward declare
class CPlayer;
class CProjectile;

using Path = std::vector<Vector3>;

class CEnemy : public IEntity
{
private:
	//Pathing
	Path* mpPath;
	Vector3 mOffset;
	int mPathPos;
	float mMoveTimer;

	//Stats
	int mHealth;
	float mSpeed;
	std::vector<CWeapon> mWeapons;
	int mValue;

protected:
	std::vector<CPlayer*>* mpPlayers = 0;
	BulletList* mpPlayerBullets = 0;
	BulletList* mpEnemyBullets = 0;

	bool mFinished;

public:
	CEnemy();
	CEnemy(Path* path, Vector3& offset);

	//Updates
	virtual void Move(float delta);
	virtual void Update(float delta);
	virtual void TakeDamage(int damage);
	virtual void CheckCollision();

	//Sets
	void SetHealth(int health);
	void SetSpeed(float speed);
	void AddWeapon(CWeapon w);
	void SetValue(int value);
	void SetPath(Path* path, Vector3& offset);

	void SetLists(std::vector<CPlayer*>* players, BulletList* playerBullets, BulletList* enemyBullets);

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