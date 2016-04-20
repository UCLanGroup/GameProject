#pragma once
#include "CEnemyManager.h"
#include "CExplosionPool.h"
#include <fstream>
#include <iostream>

//Enemies
#include "CEnemyBoss.h"
#include "CCruiser.h"
#include "CHaloBoss.h"

//Item drops
#include "CShotGun.h"
#include "CLaser.h"
#include "CWeaponDrop.h"
#include "CUpgradeDrop.h"
#include "CHealthDrop.h"
#include "CLifeDrop.h"

//Chances are out of 1000

const int kUgradeDropChance		= 15;	//1 in   50
const int kShotgunDropChance	= 5;	//1 in  200
const int kHealthDropChance		= 2;	//1 in  500
const int kLifeDropChance		= 2;	//1 in  500
const int kLaserDropChance		= 1;	//1 in 1000

CEnemyManager::CEnemyManager(string levelFile)
{
	ReadInPaths(MEDIA_FOLDER + "\\Paths.txt");
	ReadInLevel(MEDIA_FOLDER + "\\" + levelFile);

	mNumOfEnemies = 0;
	mNumOfKills = 0;
}

void CEnemyManager::SetLists(std::vector<CPlayer*>* players, BulletList* playerBullets, BulletList* enemyBullets)
{
	mpPlayers = players;
	mpPlayerBullets = playerBullets;
	mpEnemyBullets = enemyBullets;
}

//Upate all enemies
void CEnemyManager::Update(float delta)
{
	if (!(mEnemies.size() || mActiveSpawners.size())) //If both are empty
	{
		if (mInactiveSpawners.size() > 0)
		{
			do
			{
				mActiveSpawners.push_back(move(mInactiveSpawners.front()));
				mInactiveSpawners.pop_front();
			} while (mInactiveSpawners.size() > 0 && !mInactiveSpawners.front()->mPause);
		}
	}

	//Move all enemies
	auto enemy = mEnemies.begin();

	while (enemy != mEnemies.end())
	{
		(*enemy)->Update(delta);
		(*enemy)->CheckCollision();

		//Iterate by either erasing or incrementing
		if ((*enemy)->IsDead())
		{
			CreateRandomDrop((*enemy)->GetCenterPoint());
			++mNumOfKills;
			enemy = mEnemies.erase(enemy);
		}
		else if ((*enemy)->IsFinished())
		{
			enemy = mEnemies.erase(enemy);
		}
		else
		{
			++enemy;
		}
	}

	//Spawn enemies
	auto spawner = mActiveSpawners.begin();

	while (spawner != mActiveSpawners.end())
	{
		(*spawner)->mTimer += delta;

		//If it can spawn an enemy then do so
		while ((*spawner)->mTimer > (*spawner)->mSpawnRate && (*spawner)->mEnemyAmount > 0)
		{
			(*spawner)->mTimer -= (*spawner)->mSpawnRate;
			(*spawner)->mEnemyAmount--;

			//Create the enemy
			unique_ptr<CEnemy> enemy = move( CreateEnemy((*spawner)->mType, (*spawner)->mpPath, (*spawner)->mOffset) );

			//mTimer is currently the amount of time passed since the enemy should have spawned
			//So update enemy with mTimer for delta
			enemy->Update((*spawner)->mTimer);

			//Place the enemy on the list
			mEnemies.push_back(move(enemy));
		}

		//If spawner is depleted (no more enemies to spawn) then remove it from the list
		if ((*spawner)->mEnemyAmount == 0)
		{
			spawner = mActiveSpawners.erase(spawner);
		}
		else
		{
			spawner++;
		}
	}

	//Update drops
	auto drop = mDrops.begin();

	while (drop != mDrops.end())
	{
		(*drop)->Update(delta);

		for (auto player = mpPlayers->begin(); player != mpPlayers->end(); ++player)
		{
			if ((*player)->CollidesSphere(drop->get()))
			{
				(*drop)->ApplyDrop(*player);
			}
		}
		
		if ((*drop)->IsOutOfBounds() || (*drop)->IsDead())
		{
			drop = mDrops.erase(drop);
		}
		else
		{
			drop++;
		}
	}
}

//Read in the list of paths (each path is a list of waypoints)
void CEnemyManager::ReadInPaths(string& file)
{
	ifstream inFile(file);

	if (inFile.is_open())
	{
		int pathCount = 0;
		inFile >> pathCount;

		for (; pathCount > 0; pathCount--)
		{
			//Read in the number of points in the path
			int pathLength = 0;
			inFile >> pathLength;

			//Create new path
			std::unique_ptr<Path> path(new Path);

			//Read in every point in the path
			for (; pathLength > 0; pathLength--)
			{
				float x, y, z;
				inFile >> x >> y >> z;

				path->push_back(CVector3(x, y, z));
			}

			//Add the path to the list of paths
			mPaths.push_back(move(path));
		}

		//Close file once finished with it
		inFile.close();
	}
}

//Read in the level data
void CEnemyManager::ReadInLevel(string& file)
{
	//Open file
	ifstream inFile(file);

	//Check if opened
	if (inFile.is_open())
	{
		int spawnerCount = 0;
		inFile >> spawnerCount;

		//Read in every spawner
		for (; spawnerCount > 0; spawnerCount--)
		{
			int pathID;
			int type;
			float x, y, z;

			unique_ptr<SSpawner> spawner(new SSpawner);

			inFile >> type;
			inFile >> spawner->mEnemyAmount;
			inFile >> spawner->mSpawnRate;
			inFile >> spawner->mTimer;
			inFile >> pathID;
			inFile >> x >> y >> z;
			inFile >> spawner->mPause;
			
			spawner->mType = static_cast<EnemyType>(type);
			spawner->mpPath = mPaths[pathID].get();
			spawner->mOffset = CVector3(x, y, z);

			mNumOfEnemies += spawner->mEnemyAmount;

			mInactiveSpawners.push_back(move(spawner));
		}

		//Close file once finished with it
		inFile.close();
	}
}

//Create an enemy of a given type that follows the specified path with the given positional offset
unique_ptr<CEnemy> CEnemyManager::CreateEnemy(EnemyType type, Path* path, CVector3& offset)
{
	unique_ptr<CEnemy> enemy;
	switch (type)
	{
	case Basic:
		enemy.reset(new CEnemy(mpPlayers, mpPlayerBullets, mpEnemyBullets));
		enemy->SetPath(path, offset);
		return move(enemy);

	case Boss:
		enemy.reset(new CEnemyBoss(mpPlayers, mpPlayerBullets, mpEnemyBullets));
		enemy->SetPosition(offset);
		return move(enemy);

	case Heavy:
		enemy.reset(new CEnemy(mpPlayers, mpPlayerBullets, mpEnemyBullets));
		enemy->SetPath(path, offset);
		enemy->SetHealth(5);
		return move(enemy);

	case Cruiser:
		enemy.reset(new CCruiser(mpPlayers, mpPlayerBullets, mpEnemyBullets));
		enemy->SetPosition(offset);
		return move(enemy);

	case HaloBoss:
		enemy.reset(new CHaloBoss(mpPlayers, mpPlayerBullets, mpEnemyBullets));
		enemy->SetPosition(offset);
		return move(enemy);

	default:
		return 0;
		break;
	}
}

void CEnemyManager::CreateRandomDrop(CVector3& pos)
{
	int random = rand() % 1000;

	int cumulativeChance = 0;
	unique_ptr<IDrop> newDrop;

	if (random < (cumulativeChance += kUgradeDropChance)) //Upgrade drop
	{
		newDrop.reset(new CUpgradeDrop(UPGRADE_POWER_UP));
	}
	else if (random < (cumulativeChance += kShotgunDropChance)) //Weapon drop
	{
		newDrop.reset(new CWeaponDrop(new CShotGun(0, 1, 100.0f, 0.33f, 5), SHOTGUN_POWER_UP));
	}
	else if (random < (cumulativeChance += kHealthDropChance)) //Health drop
	{
		newDrop.reset(new CHealthDrop(HEALTH_POWER_UP));
	}
	else if (random < (cumulativeChance += kLaserDropChance)) //Weapon drop
	{
		newDrop.reset(new CWeaponDrop(new CLaser(0, 2, 0.1f), LASER_POWER_UP));
	}
	else if (random < (cumulativeChance += kLifeDropChance)) //Life drop
	{
		newDrop.reset(new CLifeDrop(LIFE_POWER_UP));
	}
	else
	{
		//No drop created
		return;
	}
	
	if (random < cumulativeChance)
	{
		newDrop->SetPosition(pos);
		mDrops.push_back(move(newDrop));
	}
}

bool CEnemyManager::IsLevelCleared()
{
	//Returns true if all are empty
	return !(mEnemies.size() || mActiveSpawners.size() || mInactiveSpawners.size());
}

CEnemyManager::~CEnemyManager()
{
	mEnemies.clear();
}