#include "Network.h"
bool Network::InitNetwork()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return false;
	}
	return true;
}
bool Network::CloseNetwork()
{
	closesocket(m_netSock);
	WSACleanup();
	return true;
}
bool Network::InitServer(int protocol, int port, const char* ip)
{
	m_netSock = socket(AF_INET, protocol, 0);
	SOCKADDR_IN SA;
	ZeroMemory(&SA, sizeof(SA));
	SA.sin_family = AF_INET;
	SA.sin_port = htons(port);
	if (ip == nullptr)
	{
		SA.sin_addr.s_addr = htonl(INADDR_ANY);
	}
	else
	{
		SA.sin_addr.s_addr = inet_addr(ip);
	}
	int RetB = bind(m_netSock, (sockaddr*)&SA, sizeof(SA));
	if (RetB == SOCKET_ERROR) return false;

	RetB = listen(m_netSock, SOMAXCONN);
	if (RetB == SOCKET_ERROR) return false;
	return true;
}