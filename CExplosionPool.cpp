#include "CExplosionPool.h"

CExplosionPool CExplosionPool::mPool;

//Create a pool of 100 explosion
void CExplosionPool::Init()
{
	mMesh = gEngine->LoadMesh(EXPLOSION_MESH);
	unique_ptr<SExplosion> explosion;
	for (int i = 0; i < 100; i++)
	{
		explosion.reset(new SExplosion);
		explosion->mModel = mMesh->CreateModel(0.0f, 110.0f, 0.0f);
		explosion->mStage = 1;
		explosion->mTimer = 0.0f;
		mInActive.push_back( move(explosion) );
	}
}

//Spawn an explosion at the specified location with the specified size
void CExplosionPool::Spawn(float x, float y, float z, float radius)
{
	if (mInActive.size() > 0)
	{ 
		mInActive.back()->mModel->SetPosition(x, y, z);
		mInActive.back()->mModel->Scale(radius);
		mInActive.back()->mModel->SetSkin(EXPLOSION_SPRITE + "1.png");
		mInActive.back()->mTimer = 0.0f;
		mInActive.back()->mStage = 1;

		mActive.push_back(move( mInActive.back() ));

		mInActive.pop_back();
	}
}

//Resets all the active explosions
void CExplosionPool::Reset()
{
	for (auto explosion = mActive.begin(); explosion != mActive.end(); explosion++)
	{
		(*explosion)->mModel->SetPosition(0.0f, 110.0f, 0.0f);
		(*explosion)->mModel->ResetScale();
		(*explosion)->mModel->SetSkin(EXPLOSION_SPRITE + "1.png");
		(*explosion)->mTimer = 0.0f;
		(*explosion)->mStage = 1;
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
			(*explosion)->mStage++;
			if ((*explosion)->mStage <= EXPLOSION_SPRITE_COUNT)
			{
				string s = EXPLOSION_SPRITE + to_string((*explosion)->mStage) + ".png";
				(*explosion)->mModel->SetSkin(s);
			}
			(*explosion)->mTimer -= EXPLODE_RATE;
		}

		//Remove explosion once finished
		if ((*explosion)->mStage > EXPLOSION_SPRITE_COUNT)
		{
			(*explosion)->mModel->SetPosition(0.0f, 110.0, 0.0f);
			(*explosion)->mModel->ResetScale();
			(*explosion)->mStage = 1;
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