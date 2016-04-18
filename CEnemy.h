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
	int mPathPos;
	float mMoveTimer;

	//Stats
	int mHealth;
	float mSpeed;
	int mValue;

	int mWaveID = 0;

protected:
	CVector3 mOffset;
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
	void SetWaveID(int ID);

	//Gets
	int GetHealth();
	float GetSpeed();
	int GetValue();
	int GetWaveID();
	bool IsFinished();

	//AI functions

	//Calculates the bearing (rotation from north) towards the entity
	float BearingTowards(const CVector3& pos);

	//Rotates the enemy a small amount towards the position
	//Rotates in the optimal direction
	//Returns true if it has fully rotated towards the pos
	bool RotateTowards(const CVector3& pos, float rotateAmount);

	//Moves the enemy towards the position linearly without turning
	//by an amount based on the delta and speed
	//Returns true if it reaches the target position
	bool MoveDirectlyTowards(const CVector3& pos, float delta);

	//Inherited from IEntity : IResource
	virtual void Reset();

	~CEnemy();
};