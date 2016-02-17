#pragma once
#include "Globals.h"
#include "CEnemy.h"
#include "CPool.h"

class CEnemyManager
{
private:
	//Data types

	enum EnemyType : int { Basic = 0 };
	
	struct SSpawner
	{
		EnemyType mType;
		int mEnemyAmount;
		float mSpawnRate;
		float mTimer;
		Path* mpPath;
		Vector3 mOffset;
	};

	vector_ptr<Path> mPaths;
	std::vector<CPool<CEnemy>::resource_ptr> mEnemies;
	vector_ptr<SSpawner> mSpawners;

	CPool<CEnemy>* mEnemyPool;

	//Statistics

	int mNumOfEnemies;
	int mNumOfKills;

	void ReadInPaths(string& file);
	void ReadInLevel(string& file);
	CPool<CEnemy>::resource_ptr CreateEnemy(EnemyType type, Path* path, Vector3& offset);

public:
	CEnemyManager(string levelFile);

	//Sets
	//Gets
	int GetNumOfEnemies() { return mNumOfEnemies; }
	int GetNumOfKills() { return mNumOfKills; }

	std::vector<CPool<CEnemy>::resource_ptr>& GetEnemies() { return mEnemies; }

	void Update(float delta);

	~CEnemyManager();
};