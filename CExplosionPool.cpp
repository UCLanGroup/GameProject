#include "CExplosionPool.h"

CExplosionPool CExplosionPool::mPool;

//Returns the file name for the nth explosion texture
string CExplosionPool::ExplosionTexture(int n)
{
	return EXPLOSION_SPRITE + to_string(n) + ".png";
}

//Create a pool of 100 explosion
void CExplosionPool::Init()
{
	mMesh = gEngine->LoadMesh(EXPLOSION_MESH);

	for (int i = 2; i <= EXPLOSION_SPRITE_COUNT; i++)
	{
		gEngine->Preload(EXPLOSION_MESH, 10, ExplosionTexture(i));
	}

	unique_ptr<SExplosion> explosion;
	for (int i = 0; i < 50; i++)
	{
		explosion.reset(new SExplosion);
		explosion->mModel = mMesh->CreateModel(OFF_SCREEN_X, OFF_SCREEN_Y, OFF_SCREEN_Z);
		explosion->mStage = 1;
		explosion->mTimer = 0.0f;
		explosion->mRadius = 1.0f;
		explosion->mPos = CVector3(0.0f, 0.0f, 0.0f);
		mInActive.push_back( move(explosion) );
	}
}

//Spawn an explosion at the specified location with the specified size
void CExplosionPool::Spawn(float x, float y, float z, float radius)
{
	if (mInActive.size() > 0)
	{ 
		//Store the existing model
		gEngine->CacheModel(mInActive.back()->mModel, ExplosionTexture(mInActive.back()->mStage));

		mInActive.back()->mTimer = 0.0f;
		mInActive.back()->mStage = 1;
		mInActive.back()->mRadius = radius;
		mInActive.back()->mPos = CVector3(x, y, z);

		//Get a model instance with the correct texture
		mInActive.back()->mModel = gEngine->GetModel(mMesh, ExplosionTexture(1));

		mInActive.back()->mModel->SetPosition(x, y, z);
		mInActive.back()->mModel->ResetScale();
		mInActive.back()->mModel->Scale(radius);

		mActive.push_back(move( mInActive.back() ));

		mInActive.pop_back();
	}
}

//Resets all the active explosions
void CExplosionPool::Reset()
{
	for (auto explosion = mActive.begin(); explosion != mActive.end(); explosion++)
	{
		//Store the existing model
		gEngine->CacheModel((*explosion)->mModel, ExplosionTexture((*explosion)->mStage));

		(*explosion)->mTimer = 0.0f;
		(*explosion)->mStage = 1;
		(*explosion)->mRadius = 1.0f;
		(*explosion)->mPos = CVector3(0.0f, 0.0f, 0.0f);

		//Get a model instance with the correct texture
		(*explosion)->mModel = gEngine->GetModel(mMesh, ExplosionTexture(1));

		(*explosion)->mModel->SetPosition(OFF_SCREEN_X, OFF_SCREEN_Y, OFF_SCREEN_Z);
		(*explosion)->mModel->ResetScale();

		mInActive.push_back( move(*explosion) );
	}

	//All have been moved from active to inactive, clear away the empty shell of the unique_ptrs
	mActive.clear();
}

//Animates the active explosions and remvoes them once finished
void CExplosionPool::Update(float delta)
{
	auto explosion = mActive.begin();
	while(explosion != mActive.end())
	{
		(*explosion)->mTimer += delta;
		while ((*explosion)->mTimer > EXPLODE_RATE)
		{
			if ((*explosion)->mStage < EXPLOSION_SPRITE_COUNT)
			{
				//Store the existing model
				gEngine->CacheModel((*explosion)->mModel, ExplosionTexture((*explosion)->mStage));

				(*explosion)->mStage++;

				//Get a model instance with the correct texture
				(*explosion)->mModel = gEngine->GetModel(mMesh, ExplosionTexture((*explosion)->mStage));

				(*explosion)->mModel->ResetScale();
				(*explosion)->mModel->Scale((*explosion)->mRadius);
				(*explosion)->mModel->SetPosition((*explosion)->mPos.x, (*explosion)->mPos.y, (*explosion)->mPos.z);
			}
			else
			{
				(*explosion)->mStage++;
			}
			(*explosion)->mTimer -= EXPLODE_RATE;
		}

		//Remove explosion once finished
		if ((*explosion)->mStage > EXPLOSION_SPRITE_COUNT)
		{
			(*explosion)->mModel->SetPosition(OFF_SCREEN_X, OFF_SCREEN_Y, OFF_SCREEN_Z);
			mInActive.push_back( move(*explosion) );
			explosion = mActive.erase(explosion);
		}
		else
		{
			explosion++;
		}
	}
}

//Destroy the pool
void CExplosionPool::CleanUp()
{
	for (auto explosion = mInActive.begin(); explosion != mInActive.end(); explosion++)
	{
		mMesh->RemoveModel((*explosion)->mModel);
	}
	for (auto explosion = mActive.begin(); explosion != mActive.end(); explosion++)
	{
		mMesh->RemoveModel((*explosion)->mModel);
	}
	gEngine->RemoveMesh(mMesh);
	mInActive.clear();
	mActive.clear();
}