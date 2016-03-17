#pragma once
#include "Globals.h"
#include "CWeapon.h"
#include "IEntity.h"
#include <list>

//Forward declare
class CPlayer;
class CProjectile;

using Path = std::vector<CVector3>;

class CEnemy : public IEntity
{
private:
	//Pathing
	Path* mpPath;
	CVector3 mOffset;
	int mPathPos;
	float mMoveTimer;

	//Stats
	int mHealth;
	float mSpeed;
	int mValue;

protected:
	std::vector<CPlayer*>* mpPlayers = 0;
	BulletList* mpPlayerBullets = 0;
	BulletList* mpEnemyBullets = 0;

	bool mFinished;

public:
	CEnemy(std::vector<CPlayer*>* players, BulletList* playerBullets, BulletList* enemyBullets);

	//Updates
	virtual void Move(float delta);
	virtual void Update(float delta);
	virtual void TakeDamage(int damage);
	virtual void CheckCollision();

	//Sets
	void SetHealth(int health);
	void SetSpeed(float speed);
	void SetValue(int value);
	void SetPath(Path* path, CVector3& offset);

	//Gets
	int GetHealth();
	float GetSpeed();
	int GetValue();
	bool IsFinished();

	//Inherited from IEntity : IResource
	virtual void Reset();

	~CEnemy();
};