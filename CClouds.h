#pragma once
#include <Model.h>
#include <vector>
#include <stdlib.h>

using namespace tle;

struct SCloud
{
	IModel* model;
	float speed;
};

class CClouds
{
	IMesh* mCloudMesh;
	vector<SCloud*> mClouds;
	const size_t mCLOUD_COUNT = 10;
	const string mCLOUD_MESH = "cloud.x";
	vector<string> mCloudTex = { "cloud0.png", "cloud1.png", "cloud2.png", "cloud3.png", "cloud4.png" };

	const float mMIN_SPEED = 1.0f;
	const float mMAX_SPEED = 1.5f;
	const float mMIN_Y = -10.0f;
	const float mMAX_Y = 10.0f;

public:
	CClouds();
	~CClouds();

	int GetRandInt(int low, int high);
	float GetRandFloat(float low, float high);
	void Move(float delta);
};

