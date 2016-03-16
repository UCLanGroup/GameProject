#pragma once
// Last updated: 04.02.16

#include <TL-Engine.h>
#include <SFML/audio.hpp>


#include "CGameState.h"
#include "CPlayer.h"
#include "CProjectile.h"
#include "CEnemyManager.h"
#include "CExplosionPool.h"

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
	//CPlayer mPlayer2;
	vector<CPlayer*> mPlayerList; //Used to pass a list of both players to enemies to keep track of

	unique_ptr<CEnemyManager> mEnemyManager;

	CExplosionPool* mExplosions;

	BulletList mPBullets; //Player Projectiles
	BulletList mEBullets; //Enemy Projectiles

	float mDelta = 0.0f;		// Delta time (to render previous frame)


			// SOUND
	sf::SoundBuffer mBufferShoot;
	sf::Sound mSound;
	bool mFiring = false;

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

	inline CPlayer* GetPlayer1() { return &mPlayer1; } //Don't call this in enemies, use the playerList passed to them
	//inline CPlayer* GetPlayer2() { return &mPlayer2; }

	static CPlayState* Instance()
	{
		return &mPlayState;
	}

protected: CPlayState() {}
};