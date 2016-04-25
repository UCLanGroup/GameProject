#pragma once
#include "Globals.h"
#include "CEnemy.h"
#include "IDrop.h"
#include <list>

class CEnemyManager
{
private:
	//Data types

	enum EnemyType : int { Basic = 0, Boss = 1, Heavy = 2, Cruiser = 3, HaloBoss = 4, Suicider = 5};
	
	struct SSpawner
	{
		EnemyType mType;
		int mEnemyAmount;
		float mSpawnRate;
		float mTimer;
		Path* mpPath;
		CVector3 mOffset;
		bool mPause; //Pauses the level at this spawner until all previous enemies are dead
	};

	vector_ptr<Path> mPaths;
	list_ptr<SSpawner> mInactiveSpawners;
	list_ptr<SSpawner> mActiveSpawners;
	std::list<unique_ptr<CEnemy>> mEnemies;
	list_ptr<IDrop> mDrops;

	//Statistics

	int mNumOfEnemies;
	int mNumOfKills;

	//Stuff the enemies need access to
	std::vector<CPlayer*>* mpPlayers = 0;
	BulletList* mpPlayerBullets = 0;
	BulletList* mpEnemyBullets = 0;

	//Private functions

	void ReadInPaths(string& file);
	void ReadInLevel(string& file);
	unique_ptr<CEnemy> CreateEnemy(EnemyType type, Path* path, CVector3& offset);
	void CreateRandomDrop(CVector3& pos);

	bool mNickMode = false;

public:
	CEnemyManager(string levelFile);

	//Sets
	void SetLists(std::vector<CPlayer*>* players, BulletList* playerBullets, BulletList* enemyBullets);

	//Gets
	int GetNumOfEnemies() { return mNumOfEnemies; }
	int GetNumOfKills() { return mNumOfKills; }

	list_ptr<CEnemy>& GetEnemies() { return mEnemies; }
	list_ptr<IDrop>& GetDrops() { return mDrops; }

	void DoNickCageMode();

	bool IsLevelCleared();

	void Update(float delta);

	~CEnemyManager();
};