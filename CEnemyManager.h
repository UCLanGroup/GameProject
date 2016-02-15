#pragma once
#include "Globals.h"
#include "CEnemy.h"

class CEnemyManager
{
private:
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

	void ReadInPaths(string& file);
	void ReadInLevel(string& file);
	CEnemy* CreateEnemy(EnemyType type, Path* path, Vector3& offset);

public:
	CEnemyManager(string levelFile);

	void Update(float delta);

	~CEnemyManager();
};