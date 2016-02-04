// Last updated: 04.02.16

#include "Globals.h"
#include "CGameStateHandler.h"
#include "CPlayState.h"

CPlayState CPlayState::mPlayState;

void CPlayState::Init()
{
	mBackground = gEngine->CreateSprite(INTROBG, 500.0f, 200.0f, 0.0f);
}

void CPlayState::Cleanup()
{
	gEngine->RemoveSprite(mBackground);
}

void CPlayState::Pause() {}

void CPlayState::Resume() {}

void CPlayState::HandleEvents(CGameStateHandler * game)
{
	// Keypresses go here
	if (gEngine->KeyHit(KEY_EXIT))
	{
		game->Quit();
	}
}

void CPlayState::Update(CGameStateHandler * game)
{
	mDelta = gEngine->Timer();

	// Animations go here

	// GOOD ANIMATION TEMP
	mMove += mDelta;

	if (mMove > 0.0001f)
	{
		if (mMoveUp)
		{

			mBackground->MoveY(150.0f * -mDelta);
			if (mBackground->GetY() < 100.0f)
			{
				mMoveUp = !mMoveUp;
			}
		}
		else
		{
			mBackground->MoveY(150.0f * mDelta);
			if (mBackground->GetY() > 400.0f)
			{
				mMoveUp = !mMoveUp;
			}
		}
		mMove = 0.0f;
	}
}

void CPlayState::Draw(CGameStateHandler * game)
{
	// Draw the scene
	gEngine->DrawScene();
}

