#include "CLoadScreen.h"
#include <iostream>

//For more details on how the engine uses the load screen
//see the "LoadQueuedObjects" function in the ExEgnine.cpp file
//of the TL-Extension project: https://github.com/BlazingDarkness/TL-Extension

//Construct the loading screen
CLoadScreen::CLoadScreen()
{
	mLoadBarBack = gEngine->CreateSprite(LOADING_BARBACK, kLoadBarPosX, kLoadBarPosY, 0.07f);
	mLoadBar = gEngine->CreateSprite(LOADING_BAR, kLoadBarPosX - kLoadBarSize, kLoadBarPosY, 0.06f);
	mLoadScreen = gEngine->CreateSprite(LOADING_SCREEN, 0.0f, 0.0f, 0.05f);
	mFont = gEngine->LoadFont("Rockwell", 12U);
	mTimer = 0.0f;
}

//Update the progress displayed by the loading screen
void CLoadScreen::Update(float delta)
{
	//Note: automatic updating is disabled during loading to reduce time spent on stuff other than loading
	//Therefore any animations will require manually calling the update function

	mTimer += delta;;

	float ratio = static_cast<float>(GetLoadProgress()) / static_cast<float>(GetLoadAmount());

	//Find the x position the bar needs to be
	float target = static_cast<float>(kLoadBarPosX) - kLoadBarSize + ratio * kLoadBarSize;
	mLoadBar->SetX(target);
	
	if (mTimer > 0.033f)
	{
		//Place stuff here that you only want to be done once per frame

		mTimer -= 0.033f;
		mFont->Draw(GetLoadMessage(), static_cast<int>(kLoadBarPosX), static_cast<int>(kLoadBarPosY + 40.0f), tle::kWhite);
	}

#ifdef _DEBUG
	//Output the loading message
	cout << GetLoadMessage() << endl;

	//The debug mode loads content faster due to the setskin function
	//However the iostream usage about balances it out
#endif
}

//Destroy all stuff used in the loading screen
CLoadScreen::~CLoadScreen()
{
	gEngine->RemoveSprite(mLoadScreen);
	gEngine->RemoveSprite(mLoadBar);
	gEngine->RemoveSprite(mLoadBarBack);
	gEngine->RemoveFont(mFont);
}