#include "Clouds.h"
#include <ctime>
#include "Globals.h"



CClouds::CClouds()
{
	srand( time( NULL ) );

	mCloudMesh = gEngine->LoadMesh( mQUAD_MESH );

	for (size_t i = 0; i < mCLOUD_COUNT; i++)
	{
		SCloud* cloudTemp = new SCloud;
		cloudTemp->model = mCloudMesh->CreateModel( static_cast<float>(GetRandFloat( AREA_BOUNDS_LEFT, AREA_BOUNDS_RIGHT )), 
													GetRandFloat( mMIN_Y, mMAX_Y ), 
													static_cast<float>(GetRandInt( 100.0f, 200.0f )) );
		cloudTemp->model->SetSkin( mCloudTex.at( 4 ) );
		cloudTemp->model->Scale( GetRandFloat( 10.0f, 40.0f ));
		cloudTemp->speed = GetRandFloat( mMIN_SPEED, mMAX_SPEED );
		mClouds.push_back( cloudTemp );
		cloudTemp = nullptr;
	}
	
}


CClouds::~CClouds()
{
	for(auto& cloud : mClouds)
	{
		mCloudMesh->RemoveModel( cloud->model );
	}
	delete mCloudMesh;
}

int CClouds::GetRandInt(int low, int high)
{
	return rand() % high + low;
}

float CClouds::GetRandFloat(float low, float high)
{
	return low + static_cast<float>(rand()) / static_cast<float>(RAND_MAX/(high - low));
}

// Move cloud down the screen, reset when off-screen
void CClouds::Move( float delta )
{
	for (auto& cloud : mClouds)
	{
		cloud->model->MoveLocalZ( -cloud->speed * delta );

		// reset cloud to top of screen
		if (cloud->model->GetZ() < AREA_BOUNDS_BOTTOM - 50.0f)
		{
			cloud->model->SetPosition( static_cast<float>(GetRandFloat( AREA_BOUNDS_LEFT, AREA_BOUNDS_RIGHT )),
									   GetRandFloat( mMIN_Y, mMAX_Y ),
									   static_cast<float>(GetRandInt( 100.0f, 200.0f )) );
			cloud->model->SetSkin( mCloudTex.at( GetRandInt( 0, 3 ) ) );
			//cloud->model->Scale( GetRandFloat( 10.0f, 20.0f ) );
			cloud->speed = GetRandFloat( mMIN_SPEED, mMAX_SPEED );
		}
	}
}

