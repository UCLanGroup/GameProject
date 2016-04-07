#pragma once
#include "Globals.h"

class CLoadScreen : public ILoadScreen
{
	const float kLoadBarPosX = 264;
	const float kLoadBarPosY = 646;
	const float kLoadBarSize = 744;

	ISprite* mLoadScreen;
	ISprite* mLoadBar;
	ISprite* mLoadBarBack;

public:
	CLoadScreen();

	virtual void Update(float delta);

	virtual ~CLoadScreen();
};