#include "Network.h"
#pragma once
class ClientMgr
{
public:
	char UserName[20] = { 0, };
	int SendMsg(SOCKET sock, char* msg, WORD type);
	int SendPacket(SOCKET sock, char* msg, WORD type);
	int RecvPacketHeader(SOCKET sock, UPACKET& recvPacket);
	int RecvPacketData(SOCKET sock, UPACKET& recvPacket);
};

