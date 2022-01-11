#pragma once
#include "Network.h"
class Manager
{
public:
	list<NetUser> UserList;
	HANDLE m_Mutex;

	int SendMsg(SOCKET sock, UPACKET& packet);
	int AddUser(SOCKET sock);
	int RecvUser(NetUser& user);
	int Broadcast(NetUser& user);

};

