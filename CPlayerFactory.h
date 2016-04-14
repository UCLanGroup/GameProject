#pragma once
#include "NETTIK_Networking.hpp"
#include <unordered_map>
#include "CPlayer.h"
#include "CWeapon.h"
#include "MessageQueue.h"
using std::placeholders::_1;

class CPlayerFactory
{
public:
	using PlayerList = std::vector<CPlayer*>;

private:
	PlayerList  mPlayerList;
	CPlayer*    mPLocalPlayer = nullptr;

	VirtualInstance* mPGame   = nullptr;
	IEntityManager*  mPManager = nullptr;

	void Add(CPlayer* player);
	void Remove(CPlayer* player);

public:
	PlayerList& GetList();
	CPlayer*    GetLocalPlayer();

	BulletList* mPPlayerBullets;
	BulletList* mPEnemyBullets;

	//! Sets up the pointers to the player bullet list and the enemy bullet list.
	void ForwardLists(BulletList* mPBullets, BulletList* mEBullets);

	//! Creates a local player and adds it to the network .
	void CreateLocalPlayer();

	CPlayer* GetCOOPPlayer();

	//! Invoked when: Server constructs new player.
	void NewPlayer(CPlayer* player);

	//! Invoked when: Client destructs new player.
	void RemovePlayer(CPlayer* player);

	//! Sets up the controller pointer reference.
	void Init(NETTIK::IController* pController);

	CPlayerFactory();
	~CPlayerFactory();
};

inline CPlayerFactory::PlayerList& CPlayerFactory::GetList()
{
	return mPlayerList;
}
