#pragma once
#include "CEnemyManager.h"
#include <fstream>

CEnemyManager::CEnemyManager(string levelFile)
{
	ReadInPaths(MEDIA_FOLDER + "\\Paths.txt");
	ReadInLevel(MEDIA_FOLDER + "\\" + levelFile);
}

void CEnemyManager::Update(float delta)
{
	//Move all enemies
	auto enemy = mEnemies.begin();

	while (enemy != mEnemies.end())
	{
		(*enemy)->Update(delta);

		//Iterate by either erasing or incrementing
		if ((*enemy)->IsFinished())
		{
			enemy = mEnemies.erase(enemy);
		}
		else
		{
			enemy++;
		}
	}

	//Spawn enemies
	auto spawner = mSpawners.begin();

	while (spawner != mSpawners.end())
	{
		(*spawner)->mTimer += delta;

		//If it can spawn an enemy then do so
		while ((*spawner)->mTimer > (*spawner)->mSpawnRate && (*spawner)->mEnemyAmount > 0)
		{
			(*spawner)->mTimer -= (*spawner)->mSpawnRate;
			(*spawner)->mEnemyAmount--;

			//Create the enemy
			std::unique_ptr<CEnemy> enemy(CreateEnemy((*spawner)->mType, (*spawner)->mpPath, (*spawner)->mOffset));

			//mTimer is currently the amount of time passed since the enemy should have spawned
			//So update enemy with mTimer for delta
			enemy->Update((*spawner)->mTimer);

			//Place the enemy on the list
			mEnemies.push_back(move(enemy));
		}

		//If spawner is depleted (no more enemies to spawn) then remove it from the list
		if ((*spawner)->mEnemyAmount == 0)
		{
			spawner = mSpawners.erase(spawner);
		}
		else
		{
			spawner++;
		}
	}
}

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

				path->push_back(Vector3(x, y, z));
			}

			//Add the path to the list of paths
			mPaths.push_back(move(path));
		}

		//Close file once finished with it
		inFile.close();
	}
}

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
			
			spawner->mType = static_cast<EnemyType>(type);
			spawner->mpPath = mPaths[pathID].get();
			spawner->mOffset = Vector3(x, y, z);

			mSpawners.push_back(move(spawner));
		}

		//Close file once finished with it
		inFile.close();
	}
}

CEnemy* CEnemyManager::CreateEnemy(EnemyType type, Path* path, Vector3& offset)
{
	switch (type)
	{
	case Basic:
		return new CEnemy(path, offset);
	default:
		break;
	}
}

CEnemyManager::~CEnemyManager()
{

}