#pragma once
// Last updated: 04.02.16

#include <IEngine.h>
#include <SFML/audio.hpp>


#include "CGameState.h"
#include "CPlayer.h"
#include "CBaseProjectile.h"
#include "CEnemyManager.h"
#include "CExplosionPool.h"

#include "GameNetwork.h"
using namespace tle;

class CPlayState : public CGameState
{
private:
	const float kStartBarPosX = 90;
	const float kStartBarPosY = 936;
	const float kBarSpeed = 100.0f;
	const float kBarSize = 200.0f;
	const float kFloorSize = 2000.0f;
	const float kFloorStart = 500.0f;
	const float kFloorSpeed = -100.0f;
	const int kFloorAmount = 10;

	static CPlayState mPlayState;

	ICamera* mCam;
	ISprite* mUI;
	ISprite* mUI2;
	IMesh* mFloorMesh;
	vector<IModel*> mFloor;

	vector<ISprite*> mLifeSprites;
	ISprite* mpHealthBar;
	ISprite* mpShieldBar;

	IFont* mFont;

	unique_ptr<CEnemyManager> mEnemyManager;

	CExplosionPool* mExplosions;

	BulletList* mPBullets; //Player Projectiles
	BulletList* mEBullets; //Enemy Projectiles

	float mDelta = 0.0f;		// Delta time (to render previous frame)


			// SOUND
	sf::SoundBuffer mBufferShoot;
	sf::Sound mSound;
	bool mFiring = false;

	// Networking
	GameNetwork* mPNetwork = 0;
	ENetworkType mNetworkType;

public:

	CEnemyManager* GetEnemyManager();

	void InitLives();
	void SetNetwork(ENetworkType type);
	void InitNetwork();

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

	void DrawText();
	void AnimateHealth(float delta);
	void AnimateShield(float delta);

	static CPlayState* Instance()
	{
		return &mPlayState;
	}

protected: CPlayState() {}
};