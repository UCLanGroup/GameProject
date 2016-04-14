#pragma once
#include "IControllerServer.hpp"
#include "CPlayer.h"
#include "CPlayerRealm.h"
#include "GameCodes.h"

class NetworkServer : public NETTIK::IControllerServer
{
private:
	CPlayerRealm mRealm;

public:

	void PostUpdate();

	void OnFire(const enet_uint8* data, size_t data_length, ENetPeer* enetPeer)
	{
		NetObject* object = mRealm.GetPlayer(enetPeer);
		if (!object)
			return;

		CPlayer* player;
		player = dynamic_cast<CPlayer*>(object);

		player->GetMainWeapon()->Fire();
	}

	NetworkServer() : NETTIK::IControllerServer(33)
	{
		on_enet(ENET_EVENT_TYPE_CONNECT, [this](ENetEvent& frame)
		{
			NetObject* player;
			player = mRealm.Create<CPlayer>(frame.peer);

			GetInstance("game")->GetManager("players")->Add(player);
		});

		on_enet(ENET_EVENT_TYPE_DISCONNECT, [this](ENetEvent& frame)
		{
			NetObject* player;
			player = mRealm.GetPlayer(frame.peer);

			if (!player)
				return;

			mRealm.RemoveByNetID(player->m_NetCode);
			GetInstance("game")->GetManager("players")->Remove(player->m_NetCode);
		});

		on(RPC_FIRE, std::bind(&NetworkServer::OnFire, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
	}
	virtual ~NetworkServer() { }
};