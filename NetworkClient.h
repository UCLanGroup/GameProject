#pragma once
#include "GameCodes.h"
#include "IControllerClient.hpp"
#include "CPlayer.h"
class NetworkClient : public NETTIK::IControllerClient
{
public:
	void PostUpdate()
	{

	}

	void HandleConnected(ENetEvent& evtFrame)
	{
		std::cout << "Connected to server." << std::endl;
	}

	void HandleDisconnected(ENetEvent& evtFrame)
	{
		std::cout << "Server disconnected." << std::endl;
	}

	void OnSync(const enet_uint8* data, size_t data_length, ENetPeer* enetPeer);

	void OnFire(const enet_uint8* data, size_t data_length, ENetPeer* enetPeer)
	{
		NETTIK::IPacketFactory::CProtoPacket<IMessageNewObject_Del> packet;
		packet.Read(data, data_length);

		IEntityManager* ents;
		ents = GetInstance("game")->GetManager("players");

		NetObject* player;
		player = ents->GetByNetID(packet.id());

		if (!player)
			printf("firing on invalid player %d", packet.id());
		else
			dynamic_cast<CPlayer*>(player)->GetMainWeapon()->Fire();
	}

	NetworkClient() : NETTIK::IControllerClient(33)
	{

		on_enet(ENET_EVENT_TYPE_CONNECT, std::bind(&NetworkClient::HandleConnected, this, std::placeholders::_1));
		on_enet(ENET_EVENT_TYPE_DISCONNECT, std::bind(&NetworkClient::HandleDisconnected, this, std::placeholders::_1));
		on(RPC_FIRE, std::bind(&NetworkClient::OnFire, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));
		on(RPC_SYNC, std::bind(&NetworkClient::OnSync, this, std::placeholders::_1, std::placeholders::_2, std::placeholders::_3));

	}

	virtual ~NetworkClient() { }
};