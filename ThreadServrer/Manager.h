#pragma once
#include "Network.h"
class Manager
{
public:
	list<NetUser> UserList;

	int SendMsg(SOCKET sock, UPACKET& packet);
	int AddUser(SOCKET sock);
	int RecvUser(NetUser& user);
};

