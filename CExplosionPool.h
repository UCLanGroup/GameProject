#pragma once
#include <TL-Engine.h>
#include <vector>
#include "Globals.h"

class CExplosionPool
{
private:
	struct SExplosion
	{
		IModel* mModel;
		int mStage;
		float mTimer;
	};

	IMesh* mMesh;
	vector_ptr<SExplosion> mInActive;
	vector_ptr<SExplosion> mActive;

	static CExplosionPool mPool;

	CExplosionPool() {}

public:
	//Setup and destroy
	void Init();
	void CleanUp();

	//Actions
	void Reset();
	void Spawn(float x, float y, float z, float scale);
	void Update(float delta);

	//Instance
	static CExplosionPool* Instance() { return &mPool; }
};