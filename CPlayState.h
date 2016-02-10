#pragma once
// Last updated: 04.02.16

#include <TL-Engine.h>

#include "CGameState.h"
#include "CPlayer.h"
#include "CProjectile.h"

using namespace tle;

class CPlayState : public CGameState
{
private:
	static CPlayState mPlayState;

	ICamera* mCam;
	ISprite* mUI;
	IMesh* mFloorMesh;
	IModel* mFloor;

	CPlayer mPlayer1;

	vector_ptr<CProjectile> mPBullets; //Player Projectiles
	vector_ptr<CProjectile> mEBullets; //Enemy Projectiles

	float mDelta = 0.0f;		// Delta time (to render previous frame)

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

	static CPlayState* Instance()
	{
		return &mPlayState;
	}

protected: CPlayState() {}
};