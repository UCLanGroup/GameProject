#pragma once
// Last updated: 21.02.16

#include <TL-Engine.h>

#include "CGameState.h"

using namespace tle;

class CIntroState : public CGameState
{
private:
	static CIntroState mIntroState;

	ICamera* mCam = nullptr;
	IMesh* mFloorMesh = nullptr;
	IModel* mFloor = nullptr;
	IMesh* mSkyBoxMesh = nullptr;
	IModel* mSkyBox = nullptr;
	IMesh* mPlaneMesh = nullptr;
	IModel* mPlane = nullptr;
	IMesh* mDummyMesh = nullptr;
	IModel* mDummy = nullptr;

	ISprite* mBackground;
	ISprite* mText;

	float mDelta = 0.0f;		// Delta time (to render previous frame)
	float mTextMove = 0.0f;			// For text animation
	bool mMoveUp = true;

	float mPlaneMoveSpeed = 15.0f;
	float mCameraMoveSpeed = 2.0f;

	// SOUND
	sf::SoundBuffer mBufferStart;
	sf::Sound mSound;

public:
	// Setup and destroy state
	void Init();
	void Cleanup();

	// Temporarily transition to another state
	void Pause();
	void Resume();

	// Game loop actions
	void HandleEvents(CGameStateHandler* game);
	void Update(CGameStateHandler* game);
	void Draw(CGameStateHandler* game);

	static CIntroState* Instance()
	{
		return &mIntroState;
	}

protected: CIntroState() {}
};