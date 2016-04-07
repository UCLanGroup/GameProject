#pragma once
#include "Globals.h"

//Basic loading screen with progress bar
class CLoadScreen : public ILoadScreen
{
	//Progress bar constants
	const float kLoadBarPosX = 264;
	const float kLoadBarPosY = 646;
	const float kLoadBarSize = 744;

	ISprite* mLoadScreen;
	ISprite* mLoadBar;
	ISprite* mLoadBarBack;

	IFont* mFont;

	//Note: Engine only draws the load screen at 30 fps while loading in order to speed things up
	//Timer for drawing of text, you'll see why it's needed if you comment it out
	float mTimer;

public:
	//Construct the loading screen
	CLoadScreen();

	//Update the progress displayed by the loading screen
	virtual void Update(float delta);

	//Destroy all stuff used in the loading screen
	virtual ~CLoadScreen();
};