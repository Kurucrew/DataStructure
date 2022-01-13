#pragma once
#include "NetUser.h"
class Network
{
public:
	SOCKET m_netSock;
	HANDLE m_Mutex;
	bool InitNetwork();
	bool CloseNetwork();
	bool InitServer(int protocol, int port, const char* ip = nullptr);
};

