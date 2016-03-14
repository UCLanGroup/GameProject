#pragma once
#include <IEngine.h>
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
		float mRadius;
		CVector3 mPos;
	};

	IMesh* mMesh;
	vector_ptr<SExplosion> mInActive;
	vector_ptr<SExplosion> mActive;

	static CExplosionPool mPool;

	CExplosionPool() {}

	//Returns the file name for the nth explosion texture
	string ExplosionTexture(int n);

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