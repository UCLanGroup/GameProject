#include "CLoadScreen.h"
#include <iostream>

//Construct the loading screen
CLoadScreen::CLoadScreen()
{
	mLoadBarBack = gEngine->CreateSprite(LOADING_BARBACK, kLoadBarPosX, kLoadBarPosY, 0.07f);
	mLoadBar = gEngine->CreateSprite(LOADING_BAR, kLoadBarPosX - kLoadBarSize, kLoadBarPosY, 0.06f);
	mLoadScreen = gEngine->CreateSprite(LOADING_SCREEN, 0.0f, 0.0f, 0.05f);
}

//Update the progress displayed by the loading screen
void CLoadScreen::Update(float delta)
{
	float ratio = static_cast<float>(GetLoadProgress()) / static_cast<float>(GetLoadAmount());

	//Find the x position the bar needs to be
	float target = static_cast<float>(kLoadBarPosX) - kLoadBarSize + ratio * kLoadBarSize;
	mLoadBar->SetX(target);

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
}