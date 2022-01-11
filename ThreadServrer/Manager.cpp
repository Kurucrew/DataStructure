#include "Manager.h"
int Manager::SendMsg(SOCKET sock, UPACKET& packet)
{
	char* pMsg = (char*)&packet;
	int iSendSize = 0;
	do {
		int iSendByte = send(sock, &pMsg[iSendSize],
			packet.ph.len - iSendSize, 0);
		if (iSendByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK)
			{
				return -1;
			}
		}
		iSendSize += iSendByte;
	} while (iSendSize < packet.ph.len);
	return iSendSize;
}
int Manager::AddUser(SOCKET sock)
{
	SOCKADDR_IN clientAddr;
	int iLen = sizeof(clientAddr);
	SOCKET clientSock = accept(sock,
		(sockaddr*)&clientAddr, &iLen);
	if (clientSock == SOCKET_ERROR)
	{
		return -1;
	}
	else
	{
		NetUser user;
		user.set(clientSock, clientAddr);
		WaitForSingleObject(m_Mutex, INFINITE);
		UserList.push_back(user);
		ReleaseMutex(m_Mutex);
		std::cout
			<< "ip =" << inet_ntoa(clientAddr.sin_addr)
			<< "port =" << ntohs(clientAddr.sin_port)
			<< "  " << std::endl;
		std::cout << UserList.size() << " 명 접속중.." << std::endl;
	}
	return 1;
}
int Manager::RecvUser(NetUser& user)
{
	char szRecvBuffer[1024] = { 0, };
	int iRecvByte = recv(user.m_Socket, szRecvBuffer, 1024, 0);
	if (iRecvByte == 0)
	{
		return 0;
	}
	if (iRecvByte == SOCKET_ERROR)
	{
		return -1;
	}
	user.DispatchRead(szRecvBuffer, iRecvByte);
	return 1;
}
int Manager::Broadcast(NetUser& user)
{
	if (user.m_packetPool.size() > 0)
	{
		list<Packet>::iterator iter;
		for (NetUser& send : UserList)
		{
			int Ret = SendMsg(send.m_Socket, (*iter).m_uPacket);
			if (Ret <= 0)
			{
				send.m_Connect = false;
			}
		}
		iter = user.m_packetPool.erase(iter);
	}
	return -1;
}