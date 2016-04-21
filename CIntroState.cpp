// Last updated: 21.02.16

#include "Globals.h"
#include "CGameStateHandler.h"
#include "CIntroState.h"
#include "CPlayState.h"
#include <iostream>

CIntroState CIntroState::mIntroState;

void CIntroState::Init()
{
	// Menu screen goes here
	mBackground = gEngine->CreateSprite(INTRO_BG, 0.0f, 0.0f, 0.8f);
	mText = gEngine->CreateSprite(INTRO_START, 0.0f, 300.0f, 0.9f);

	mFloorMesh = gEngine->LoadMesh(GROUND_MESH);
	mFloor = mFloorMesh->CreateModel(-6.0f, -10.0f, -5.5f);
	mFloor->SetSkin(GRASS_TEX);

	mSkyBoxMesh = gEngine->LoadMesh(SKYBOX_MESH);
	mSkyBox = mSkyBoxMesh->CreateModel(0.0f, -960.0f, 0.0f);

	mPlaneMesh = gEngine->LoadMesh(PLAYER_MESH);
	mPlane = mPlaneMesh->CreateModel(0.0f, 10.0f, 150.0f);
	mPlane->Scale(6.0f);
	mPlane->RotateY(180.0f);

	// CAMERA
	mDummyMesh = gEngine->LoadMesh(DUMMY_MESH);
	mDummy = mDummyMesh->CreateModel(0.0f, 10.0f, 150.0f);

	mCam = gEngine->CreateCamera(kManual, 0.0f, 30.0f, -150.0f);
	mCam->AttachToParent(mDummy);
	mCam->RotateLocalX(10.0f);

	// GAME_MUSIC
	//Warning, this is never destroyed, engine does handle clean up of non-destroyed stuff so it's not really bad, just shitty
	if (!mMusic) //If it doesn't already exist
	{
		mMusic = gEngine->CreateMusic(MENU_MUSIC);
		mMusic->Play();
	}

	// SOUND
	mIntroSound = gEngine->CreateSound(SOUND_START);
}

void CIntroState::Cleanup() 
{
	gEngine->RemoveSprite(mBackground);
	gEngine->RemoveSprite(mText);
	gEngine->RemoveCamera(mCam);
	mFloorMesh->RemoveModel(mFloor);
	gEngine->RemoveMesh(mFloorMesh);
	mSkyBoxMesh->RemoveModel(mSkyBox);
	gEngine->RemoveMesh(mSkyBoxMesh);
	mDummyMesh->RemoveModel(mDummy);
	gEngine->RemoveMesh(mDummyMesh);
	mPlaneMesh->RemoveModel(mPlane);
	gEngine->RemoveMesh(mPlaneMesh);
	gEngine->RemoveSound(mIntroSound);
}


void CIntroState::Pause() {}

void CIntroState::Resume() {}


void CIntroState::HandleEvents(CGameStateHandler* game)
{
	// Keypresses go here
	if (gEngine->KeyHit(KEY_EXIT))
	{
		game->Quit();
	}

	if (gEngine->KeyHit(KEY_START))
	{
		mMusic->Stop();
		mIntroSound->Play();
		game->ChangeState(CPlayState::Instance());
	}
}

void CIntroState::Update(CGameStateHandler* game)
{
	// Restart music if coming from game over / menu
	if (mMusic->GetStatus() == sf::SoundSource::Stopped)
	{
		mMusic->Play();
	}

	mDelta = gEngine->Timer();

	// Animations go here
	mTextMove += mDelta;

	// Start text
	if (mTextMove > 0.0001f)
	{
		mPlane->RotateY(mPlaneMoveSpeed * mDelta);
		mDummy->RotateY(-mCameraMoveSpeed * mDelta);

		if (mMoveUp)
		{
			mText->MoveY(15.0f * -mDelta);
			if (mText->GetY() < 295.0f)
			{
				mMoveUp = !mMoveUp;
			}
		}
		else
		{
			mText->MoveY(15.0f * mDelta);
			if (mText->GetY() > 305.0f)
			{
				mMoveUp = !mMoveUp;
			}
		}
		mTextMove = 0.0f;
	}

}

void CIntroState::Draw(CGameStateHandler* game)
{
	// Draw the scene
	gEngine->DrawScene();
}