#pragma once
#include "NETTIK_Networking.hpp"
#include "GameCodes.h"
#include "NetworkServer.h"
#include "NetworkClient.h"
#include "CPlayerFactory.h"

enum ENetworkType
{
	kNetworkServer,
	kNetworkClient
};

class GameNetwork
{
private:
	ENetworkType mType;
	NETTIK::IController* mPController = 0;


	CPlayerFactory mPlayers;

	static GameNetwork mInstance;

public:
	ENetworkType GetType();
	CPlayerFactory& GetPlayerFactory();

	template <class T>
	T* GetController();

	static GameNetwork* Instance();

	void FireWeapon(IEntity* player)
	{
		if (mType == kNetworkClient)
		{
			// dirty hack.
			NETTIK::IPacketFactory::CProtoPacket<IMessageNewObject_Del> packet;

			if (player != nullptr)
				packet.set_id(dynamic_cast<NetObject*>(player)->m_NetCode);

			packet.SetReliable();
			packet.SetCode(RPC_FIRE);
			packet.Dispatch();

		}
		else
		{
			CPlayer* recipient;
			recipient = mPlayers.GetCOOPPlayer();

			if (!recipient)
				return;

			// dirty hack.
			NETTIK::IPacketFactory::CProtoPacket<IMessageNewObject_Del> packet;

			if (player != nullptr)
				packet.set_id(dynamic_cast<NetObject*>(player)->m_NetCode);

			packet.SetReliable();
			packet.SetCode(RPC_FIRE);

			printf("peer = %p\n", recipient->m_pPeer);
			packet.SetPeer(recipient->m_pPeer);
			packet.Dispatch();
		}
	}

	void InitNETTIK(ENetworkType type)
	{

		mType = type;

		if (type == kNetworkServer)
			mPController = new NetworkServer();
		else if (type == kNetworkClient)
			mPController = new NetworkClient();

	}

	void Init();

	void Stop()
	{

		mPController->Stop();
	}
};

inline GameNetwork* GameNetwork::Instance()
{
	return &mInstance;
}

inline ENetworkType GameNetwork::GetType()
{
	return mType;
}

inline CPlayerFactory& GameNetwork::GetPlayerFactory()
{
	return mPlayers;
}

template <class T>
inline T* GameNetwork::GetController()
{
	return dynamic_cast<T*>(mPController);
}