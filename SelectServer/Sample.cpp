#include "Network.h"
list<NetUser> UserList;
int SendMsg(SOCKET sock, UPACKET& packet)
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
int AddUser(SOCKET sock)
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
		UserList.push_back(user);
		std::cout
			<< "ip =" << inet_ntoa(clientAddr.sin_addr)
			<< "port =" << ntohs(clientAddr.sin_port)
			<< "  " << std::endl;
		std::cout << UserList.size() << " 명 접속중.." << std::endl;
	}
	return 1;
}
int RecvUser(NetUser& user)
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
	//user.DispatchRead(szRecvBuffer, iRecvByte);
	return 1;
}
int main()
{
	Network Net;
	Net.InitNetwork();
	Net.InitServer(SOCK_STREAM, 10000);
	cout << "서버 가동" << endl;

	FD_SET rSet;
	FD_SET wSet;
	timeval timeout;

	while (1)
	{
		FD_ZERO(&rSet);
		FD_ZERO(&wSet);
		FD_SET(Net.m_netSock, &rSet);
		list<NetUser>::iterator iter;

		for (iter = UserList.begin(); iter != UserList.end();)
		{
			if ((*iter).m_Connect == false)
			{
				std::cout << (*iter).m_Name << " 접속종료됨." << std::endl;
				iter = UserList.erase(iter);
				continue;
			}
			FD_SET((*iter).m_Socket, &rSet);
			// 만약 user에서 보낸 페킷이 있으면
			if ((*iter).m_packetPool.size() > 0)
			{
				FD_SET((*iter).m_Socket, &wSet);
			}
			iter++;
		}
		int iRet = select(0, &rSet, &wSet, NULL, &timeout);
		if (iRet == 0)
		{
			continue;
		}
		if (FD_ISSET(Net.m_netSock, &rSet))
		{
			if (AddUser(Net.m_netSock) <= 0)
			{
				break;
			}
		}
		for (NetUser& user : UserList)
		{
			if (FD_ISSET(user.m_Socket, &rSet))
			{
				int iRet = RecvUser(user);
				if (iRet <= 0)
				{
					user.m_Connect = false;
				}
			}
		}
		for (NetUser& user : UserList)
		{
			if (FD_ISSET(user.m_Socket, &wSet))
			{
				if (user.m_packetPool.size() > 0)
				{
					std::list<Packet>::iterator iter;
					for (iter = user.m_packetPool.begin();
						iter != user.m_packetPool.end(); )
					{
						for (NetUser& senduser : UserList)
						{
							int iRet = SendMsg(senduser.m_Socket, (*iter).m_uPacket);
							if (iRet <= 0)
							{
								senduser.m_Connect = false;
							}
						}
						iter = user.m_packetPool.erase(iter);
					}
				}
			}
		}
	}
}
