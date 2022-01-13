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
int Manager::SendMsg(SOCKET sock, char* msg, WORD type)
{
	UPACKET packet;
	ZeroMemory(&packet, sizeof(packet));
	packet.ph.len = strlen(msg) + PACKET_HEADER_SIZE;
	packet.ph.type = type;
	memcpy(packet.msg, msg, strlen(msg));
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
bool Manager::AddUser(SOCKET sock)
{
	SOCKADDR_IN clientAddr;
	int iLen = sizeof(clientAddr);
	SOCKET clientSock = accept(sock,
		(sockaddr*)&clientAddr, &iLen);
	u_long on = 1;
	ioctlsocket(clientSock, FIONBIO, &on);
	if (clientSock == SOCKET_ERROR)
	{
		int iError = WSAGetLastError();
		if (iError != WSAEWOULDBLOCK)
		{
			std::cout << "ErrorCode=" << iError << std::endl;
			return true;
		}
	}
	else
	{
		char i;
		cout
			<< "ip =" << inet_ntoa(clientAddr.sin_addr)
			<< "port =" << ntohs(clientAddr.sin_port)
			<< "  立加 夸没吝(Y/N)" << endl;
		cin >> i;
		if (i=='y'||i=='Y')
		{
			NetUser user;
			user.set(clientSock, clientAddr);
			WaitForSingleObject(m_Mutex, INFINITE);
			UserList.push_back(user);
			ReleaseMutex(m_Mutex);
			std::cout << UserList.size() << " 疙 立加吝.." << std::endl;
			RecvUser(user);
			
			list<NetUser>::iterator userIter;
			for (userIter = UserList.begin();
				userIter != UserList.end();)
			{
				int iRet = Broadcast(*userIter);
				if (iRet <= 0)
				{
					userIter = UserList.erase(userIter);
				}
				else
				{
					userIter++;
				}
			}
		}
		else
		{
			char Buffer[] = "立加 夸没 芭何";
			SendMsg(clientSock, Buffer, PACKET_SYSTEM_MSG);
			closesocket(clientSock);
			return true;
		}
	}
	return true;
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
		int iError = WSAGetLastError();
		if (iError != WSAEWOULDBLOCK)
		{
			return -1;
		}
		return 2;
	}
	user.DispatchRead(szRecvBuffer, iRecvByte);
	return 1;
}
int Manager::Broadcast(NetUser& user)
{
	if (user.m_packetPool.size() > 0)
	{
		list<Packet>::iterator iter;
		for (iter = user.m_packetPool.begin(); iter != user.m_packetPool.end();)
		{
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
	}
	return 1;
}