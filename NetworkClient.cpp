#include "NetworkClient.h"
#include "CPlayState.h"

void NetworkClient::OnSync(const enet_uint8* data, size_t data_length, ENetPeer* enetPeer)
{
	NETTIK::IPacketFactory::CProtoPacket<IMessageNewObject_Del> packet;
	packet.Read(data, data_length);

	float time;
	time = static_cast<float>(packet.id());

	CPlayState::Instance()->GetEnemyManager()->SetSpawnerTimes(time);
}