#pragma once
#include "Globals.h"
#include "CEnemy.h"
#include "CPool.h"
#include <list>

class CEnemyManager
{
private:
	//Data types

	enum EnemyType : int { Basic = 0, Boss = 1 };
	
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
	vector_ptr<SSpawner> mSpawners;
	std::list<res_ptr<CEnemy>> mEnemies;

	CPool<CEnemy>* mEnemyPool;

	//Statistics

	int mNumOfEnemies;
	int mNumOfKills;

	void ReadInPaths(string& file);
	void ReadInLevel(string& file);
	res_ptr<CEnemy> CreateEnemy(EnemyType type, Path* path, Vector3& offset);

	//Stuff the enemies need access to
	std::vector<CPlayer*>* mpPlayers = 0;
	BulletList* mpPlayerBullets = 0;
	BulletList* mpEnemyBullets = 0;

public:
	CEnemyManager(string levelFile);

	//Sets
	void SetLists(std::vector<CPlayer*>* players, BulletList* playerBullets, BulletList* enemyBullets);

	//Gets
	int GetNumOfEnemies() { return mNumOfEnemies; }
	int GetNumOfKills() { return mNumOfKills; }

	std::list<res_ptr<CEnemy>>& GetEnemies() { return mEnemies; }

	void Update(float delta);

	~CEnemyManager();
};