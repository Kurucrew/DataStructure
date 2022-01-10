#include "NetUser.h"

void NetUser::set(SOCKET Socket, SOCKADDR_IN Addr)
{
	ZeroMemory(m_Buffer, sizeof(char) * 2048);
	m_StartPos = 0;
	m_ReadPos = 0;
	m_RecentPos = 0;
	m_Connect = true;

	m_Socket = Socket;
	m_Addr = Addr;
	m_Name = inet_ntoa(Addr.sin_addr);
	m_Port = ntohs(Addr.sin_port);
}