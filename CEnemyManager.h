#pragma once
#include "Globals.h"
#include "CEnemy.h"

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
	vector_ptr<CEnemy> mEnemies;
	vector_ptr<SSpawner> mSpawners;

	//Statistics

	int mNumOfEnemies;
	int mNumOfKills;

	void ReadInPaths(string& file);
	void ReadInLevel(string& file);
	CEnemy* CreateEnemy(EnemyType type, Path* path, Vector3& offset);

public:
	CEnemyManager(string levelFile);

	//Sets
	//Gets
	int GetNumOfEnemies() { return mNumOfEnemies; }
	int GetNumOfKills() { return mNumOfKills; }

	vector_ptr<CEnemy>& GetEnemies() { return mEnemies; }

	void Update(float delta);

	~CEnemyManager();
};