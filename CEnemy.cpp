#define _USE_MATH_DEFINES
#include "CEnemy.h"
#include "CPlayer.h"
#include <algorithm>

const int kHealth = 1;
const float kSpeed = 1.0f;
const int kValue = 10;
const float kRadius = 5.0f;
const int kPlayerCollisionDamage = 50;

CEnemy::CEnemy(std::vector<CPlayer*>* players, BulletList* playerBullets, BulletList* enemyBullets)
{
	//Model
	SetMesh(F16_ENEMY_MESH);
	SetRadius(kRadius);

	mpPlayers = players;
	mpEnemyBullets = enemyBullets;
	mpPlayerBullets = playerBullets;

	//All other stats are reset
	Reset();
}

//Updates

void CEnemy::Move(float delta)
{
	mMoveTimer += delta * mSpeed;
	if (mMoveTimer > 1.0f)
	{
		mMoveTimer -= 1.0f;
		mPathPos++;
	}
	if (mPathPos < static_cast<int>(mpPath->size() - 2))
	{
		//spline
		int highestPoint = mpPath->size() - 1;
		CVector3 p1 = (*mpPath)[min(highestPoint, mPathPos)];
		CVector3 p2 = (*mpPath)[min(highestPoint, mPathPos + 1)];
		CVector3 p3 = (*mpPath)[min(highestPoint, mPathPos + 2)];
		CVector3 p4 = (*mpPath)[min(highestPoint, mPathPos + 3)];

		CVector3 A = p4 - p1 + (p2 * 3.0f) - (p3 * 3.0f);
		CVector3 B = (p1 * 2.0f) - (p2 * 5.0f) + (p3 * 4) - p4;
		CVector3 C = p3 - p1;
		CVector3 D = p2 * 2;

		CVector3 newPos = ((A * (mMoveTimer * mMoveTimer * mMoveTimer)) + (B * (mMoveTimer * mMoveTimer)) + (C * mMoveTimer) + D) * 0.5f;
		newPos = newPos + mOffset;

		//Calculate bearing from north
		float xDif = newPos.x - mModel->GetX();
		float zDif = newPos.z - mModel->GetZ();
		float angle = 90.0f - atan2f(zDif, xDif) * (180.0f / static_cast<float>(M_PI));
		
		//Reset orientation then apply new angle
		mModel->ResetOrientation();
		mModel->RotateY(angle);

		mModel->SetPosition(newPos.x, newPos.y, newPos.z);
	}
	else
	{
		mFinished = true;
	}
}

void CEnemy::Update(float delta)
{
	Move(delta);
}

void CEnemy::TakeDamage(int damage)
{
	mHealth -= damage;
	if (mHealth <= 0)
	{
		SetDead(true);
		mFinished = true;
	}
}

void CEnemy::CheckCollision()
{
	if (mpPlayerBullets == 0) return;

	auto bullet = mpPlayerBullets->begin();
	while (bullet != mpPlayerBullets->end() && !IsDead())
	{
		if (CollidesSphere(bullet->get())) //Result is false if either entity is already dead
		{
			TakeDamage((*bullet)->GetDamage());
			
			if (IsDead())	//If killed by the bullet
			{
				//Check if the bullet was fired by a player, if so then add to their score
				for (auto player = mpPlayers->begin(); player != mpPlayers->end(); ++player)
				{
					if (dynamic_cast<IEntity*>(*player) == (*bullet)->GetParent())
					{
						(*player)->IncreaseScore(mValue);
					}
				}
			}

			(*bullet)->SetDead(true);
			bullet = mpPlayerBullets->erase(bullet);
		}
		else
		{
			++bullet;
		}
	}

	//Check for collision with the players
	for (auto player = mpPlayers->begin(); player != mpPlayers->end() && !IsDead(); ++player)
	{
		if (CollidesSphere(*player)) //Result is false if either entity is already dead
		{
			(*player)->TakeDamage(kPlayerCollisionDamage);
			TakeDamage(kPlayerCollisionDamage);

			if (IsDead())
			{
				(*player)->IncreaseScore(mValue);
			}
		}
	}
}

//Sets

void CEnemy::SetHealth(int health)
{
	mHealth = health;
}

void CEnemy::SetSpeed(float speed)
{
	mSpeed = speed;
}

void CEnemy::SetValue(int value)
{
	mValue = value;
}

void CEnemy::SetPath(Path* path, CVector3& offset)
{
	mpPath = path;
	mOffset = offset;
}

void CEnemy::SetWaveID(int ID)
{
	mWaveID = ID;
}

//Gets

int CEnemy::GetHealth()
{
	return mHealth;
}

float CEnemy::GetSpeed()
{
	return mSpeed;
}

int CEnemy::GetValue()
{
	return mValue;
}

int CEnemy::GetWaveID()
{
	return mWaveID;
}

bool CEnemy::IsFinished()
{
	return mFinished;
}

//AI functions

//Calculates the bearing (rotation from north) towards the entity
float CEnemy::BearingTowards(const CVector3& pos)
{
	CVector3 dif = pos - GetCenterPoint();

	//Calculate the bearing from north
	return 90.0f - (atan2f(dif.z, dif.x) * (180.0f / static_cast<float>(M_PI)));
}

//Rotates the enemy a small amount towards the position
//Rotates in the optimal direction
//Returns true if it has fully rotated towards the pos
bool CEnemy::RotateTowards(const CVector3& pos, float rotateAmount)
{
	float rotation = GetRotation();
	float rotDif = BearingTowards(pos) - rotation;

	if ((rotDif < 0.0f && rotDif > -180.0f) || (rotDif > 180.0f))
	{
		mModel->RotateY(-rotateAmount);
	}
	else
	{
		mModel->RotateY(rotateAmount);
	}

	return (abs(rotDif) < abs(rotateAmount));
}

//Moves the enemy towards the position linearly without turning
//by an amount based on the delta and speed
//Returns true if it reaches the target position
bool CEnemy::MoveDirectlyTowards(const CVector3& pos, float delta)
{
	CVector3 posDif = pos - GetCenterPoint();
	float distance = posDif.Length();
	float distToTravel = delta * mSpeed;

	if (distance > distToTravel)
	{
		CVector3 moveAmount = posDif * (distToTravel / distance);
		mModel->Move(moveAmount.x, moveAmount.y, moveAmount.z);
		return false;
	}
	else
	{
		SetPosition(pos);
		return true;
	}
}

//Inherited from IResource

void CEnemy::Reset()
{
	//Pathing
	mPathPos = 0;
	mMoveTimer = 0.0f;
	mFinished = false;
	SetDead(false);

	//Default
	mHealth = kHealth;
	mSpeed = kSpeed;
	mValue = kValue;
}

CEnemy::~CEnemy()
{

}