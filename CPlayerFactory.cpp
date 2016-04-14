#include "CPlayerFactory.h"

void CPlayerFactory::ForwardLists(BulletList* mPBullets, BulletList* mEBullets)
{
	mPPlayerBullets = mPBullets;
	mPEnemyBullets = mEBullets;
}

void CPlayerFactory::Add(CPlayer* player)
{
	mPlayerList.push_back(player);
}

void CPlayerFactory::Remove(CPlayer* player)
{
	auto player_it = std::find(mPlayerList.begin(), mPlayerList.end(), player);

	if (player_it != mPlayerList.end())
	{
		mPlayerList.erase(player_it);
	}
}

void CPlayerFactory::CreateLocalPlayer()
{
	mPLocalPlayer = new CPlayer();
	mPLocalPlayer->Init();
	mPLocalPlayer->SetLists(mPPlayerBullets, mPEnemyBullets);
	mPGame->GetManager("players")->Add(mPLocalPlayer);
	//Add(mPLocalPlayer);
}

void CPlayerFactory::NewPlayer(CPlayer* player)
{
	SMessage msg;
	msg.type = kMessagePlayerInit;
	msg.entity = player;

	CMessageQueue::Instance()->Send("events", msg);
	Add(player);
}

void CPlayerFactory::RemovePlayer(CPlayer* player)
{
	SMessage msg;
	msg.type = kMessagePlayerCleanup;
	msg.entity = player;

	CMessageQueue::Instance()->Send("events", msg);
	Remove(player);
}

void CPlayerFactory::Init(NETTIK::IController* pController)
{
	mPGame = pController->GetInstance("game");

	mPManager = mPGame->CreateManager<CPlayer>("players",
		std::bind(&CPlayerFactory::NewPlayer, this, _1),
		std::bind(&CPlayerFactory::RemovePlayer, this, _1)
		);
}

CPlayer* CPlayerFactory::GetCOOPPlayer()
{
	for (auto& player : mPlayerList)
	{
		if (player->m_pPeer != nullptr)
			return player;
	}

	return nullptr;
}

CPlayer* CPlayerFactory::GetLocalPlayer()
{
	// If the player wasn't created locally.
	if (mPLocalPlayer == nullptr)
	{
		int i = 0;
		for (auto player : mPlayerList)
		{
			if (player->m_Controller == NET_CONTROLLER_LOCAL)
			{
				mPLocalPlayer = player;
				break;
			}
		}
	}

	return mPLocalPlayer;
}

CPlayerFactory::CPlayerFactory()
{
}

CPlayerFactory::~CPlayerFactory()
{

}