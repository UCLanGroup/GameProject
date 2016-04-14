#include "NetworkServer.h"
#include "CPlayState.h"

void NetworkServer::PostUpdate()
{

	NETTIK::IPacketFactory::CProtoPacket<IMessageNewObject_Del> packet;
	packet.set_id(static_cast<uint32_t>(CPlayState::Instance()->GetEnemyManager()->GetFirstSpawnerTime()));

	CPlayer* recipient;
	recipient = GameNetwork::Instance()->GetPlayerFactory().GetCOOPPlayer();

	if (!recipient)
		return;

	packet.SetUnsequenced();
	packet.SetCode(RPC_SYNC);
	packet.SetPeer(recipient->m_pPeer);
	packet.Dispatch();
	printf("sync to %f\n", static_cast<float>(packet.id()));
}
