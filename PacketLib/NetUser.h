#pragma once
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <list>
#include <string>
#include "Packet.h"
#pragma comment	(lib, "ws2_32.lib")
using namespace std;
class NetUser
{
public:
	SOCKET m_Socket;
	SOCKADDR_IN m_Addr;
	string m_Name;
	char m_ChattName[20] = {0, };
	unsigned short m_Port;
	bool m_Connect;
	
	char m_Buffer[2048];
	int m_StartPos;
	int m_RecentPos;
	int m_ReadPos;
	list<Packet> m_packetPool;

	void set(SOCKET Socket, SOCKADDR_IN Addr);
	int DispatchRead(char* szRecvBuffer, int iRecvByte);
};

