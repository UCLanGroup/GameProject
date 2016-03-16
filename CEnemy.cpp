#define _USE_MATH_DEFINES
#include "CEnemy.h"
#include "CPlayer.h"
#include "CExplosionPool.h"
#include <algorithm>

const int kHealth = 1;
const float kSpeed = 1.0f;
const int kValue = 10;
const float kRadius = 5.0f;

CEnemy::CEnemy()
{
	//Model
	SetMesh(DEFAULT_ENEMY_MESH);
	SetRadius(kRadius);

	//All other stats are reset
	Reset();
}

CEnemy::CEnemy(Path* path, tlx::CVector3& offset) : CEnemy()
{
	//Pathing
	mpPath = path;
	mOffset = offset;
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

		/*
		//Attempt using dot product to rotate towards new position

		Vector3 oldPos(mModel->GetX(), mModel->GetLocalY(), mModel->GetZ());
		float matrix[16];
		mModel->GetMatrix(&(matrix[0]));
		Vector3 forward(matrix[0], matrix[1], matrix[2]); //Get the direction the model is facing
		Vector3 direction = newPos - oldPos;

		float dot = (forward * direction) / (forward.Length() * direction.Length());
		float angle = acosf(dot);

		if (angle > 0.01f)
		{
			if (dot > 0.0f)
			{
				mModel->RotateLocalY(angle);
			}
			else
			{
				mModel->RotateLocalY(-angle);
			}
		}*/

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
		if (CollidesSphere(bullet->get()))
		{
			TakeDamage((*bullet)->GetDamage());
			
			if (IsDead())	//If killed by the bullet
			{
				CVector3 loc = GetCenterPoint();
				CExplosionPool::Instance()->Spawn(loc.x, loc.y, loc.z, GetRadius());

				//Check if the bullet was fired by a player, if so then add to their score
				for (auto player = mpPlayers->begin(); player != mpPlayers->end(); ++player)
				{
					if (dynamic_cast<IEntity*>(*player) == (*bullet)->GetParent())
					{
						(*player)->IncreaseScore(mValue);
					}
				}
			}

			CExplosionPool::Instance()->Spawn((*bullet)->GetCenterPoint().x, 0.0f, (*bullet)->GetCenterPoint().z, (*bullet)->GetRadius());
			bullet = mpPlayerBullets->erase(bullet);
		}
		else
		{
			bullet++;
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

void CEnemy::AddWeapon(CWeapon w) //Perposely use copy constructor
{
	mWeapons.push_back(w);
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

void CEnemy::SetLists(std::vector<CPlayer*>* players, BulletList* playerBullets, BulletList* enemyBullets)
{
	mpPlayers = players;
	mpPlayerBullets = playerBullets;
	mpEnemyBullets = enemyBullets;
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

std::vector<CWeapon>* CEnemy::GetWeapons()
{
	return &mWeapons;
}

int CEnemy::GetValue()
{
	return mValue;
}

bool CEnemy::IsFinished()
{
	return mFinished;
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