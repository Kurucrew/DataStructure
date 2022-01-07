#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<iostream>
#include<winsock2.h>
#include <list>
#include <string>
#include "Packet.h"
#pragma comment (lib, "ws2_32.lib")
using namespace std;
struct User
{
	SOCKET m_Socket;
	SOCKADDR_IN m_Addr;
	string m_Name;
	unsigned short m_Port;
	void set(SOCKET Socket, SOCKADDR_IN Addr)
	{
		m_Socket = Socket;
		m_Addr = Addr;
		m_Name = inet_ntoa(Addr.sin_addr);
		m_Port = ntohs(Addr.sin_port);
	}
};

int SendMsg(SOCKET sock, char* msg, WORD type)
{//1.패킷 생성
	UPACKET packet;
	ZeroMemory(&packet, sizeof(packet));
	packet.ph.len = strlen(msg) + PACKET_HEADER_SIZE;
	packet.ph.type = type;
	memcpy(packet.msg, msg, strlen(msg));
	//2.패킷 전송
	char* pMsg = (char*)&packet;
	int SendSize = 0;
	do
	{
		int SendByte = send(sock, &pMsg[SendSize], packet.ph.len - SendSize, 0);
		if (SendByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK) return -1;
		}
		SendSize += SendByte;
	} while (SendSize < packet.ph.len);
	return SendSize;
}
int SendMsg(SOCKET sock, UPACKET& packet)
{
	char* pMsg = (char*)&packet;
	int SendSize = 0;
	do
	{
		int SendByte = send(sock, &pMsg[SendSize], packet.ph.len - SendSize, 0);
		if (SendByte == SOCKET_ERROR)
		{
			if (WSAGetLastError() != WSAEWOULDBLOCK) return -1;
		}
		SendSize += SendByte;
	} 
	while (SendSize < packet.ph.len);
	return SendSize;
}
void main()
{
	//1.소켓 환경설정 및 활성화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return;
	}
	//2.소켓 생성
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN SA;
	ZeroMemory(&SA, sizeof(SA));
	SA.sin_family = AF_INET;
	SA.sin_port = htons(10000);
	SA.sin_addr.s_addr = htonl(INADDR_ANY);//들어오는 모든 ip를 받는 매크로
	//3.바인딩
	int RetB = bind(sock, (sockaddr*)&SA, sizeof(SA));
	if (RetB == SOCKET_ERROR) return;
	//4.리스닝
	RetB = listen(sock, SOMAXCONN);
	if (RetB == SOCKET_ERROR) return;
	//5.억셉팅
	SOCKADDR_IN clientAddr;
	int Len = sizeof(clientAddr);
	cout << "서버 가동" << endl;
	u_long on = 1;
	ioctlsocket(sock, FIONBIO, &on);
	list<User> UserList;
	while (1)
	{
		//유저의 접속을 체크
		SOCKET clientSock = accept(sock, (sockaddr*)&clientAddr, &Len);
		if (clientSock == SOCKET_ERROR)
		{
			int Error = WSAGetLastError();
			if (Error != WSAEWOULDBLOCK)
			{
				break;
			}
		}
		else
		{
			//접속한 유저가 있는경우 유저리스트에 추가
			User user;
			user.set(clientSock, clientAddr);
			UserList.push_back(user);
			cout << "ip : " << user.m_Name << " port : " << user.m_Port << endl;
			cout << UserList.size() << "명 접속" << endl;
		}
		if (UserList.size() > 0)
		{
			list<User>::iterator RecvIter;
			for (RecvIter = UserList.begin(); RecvIter != UserList.end();)
			{
				User user = *RecvIter;
				char szRecvBuffer[256] = { 0, };
				UPACKET recvPacket;
				ZeroMemory(&recvPacket, sizeof(recvPacket));
				int iRecvSize = 0;
				do
				{
					int RecvByte = recv(user.m_Socket, szRecvBuffer, PACKET_HEADER_SIZE, 0);
					iRecvSize += RecvByte;
					if (RecvByte == 0)
					{
						cout << "ip : " << user.m_Name << " port : " << user.m_Port << " | 접속 종료" << endl;
						closesocket(user.m_Socket);
						RecvIter = UserList.erase(RecvIter);//유저가 접속을 종료하면 유저리스트에서 제거
						cout << UserList.size() << "명 남음" << endl;
						break;
					}
					if (RecvByte == SOCKET_ERROR)
					{
						int iError = WSAGetLastError();
						if (iError != WSAEWOULDBLOCK)
						{
							RecvIter = UserList.erase(RecvIter);
							cout << "ip : " << user.m_Name << " port : " << user.m_Port << " | 비정상 접속 종료" << endl;
							cout << UserList.size() << "명 남음" << endl;
							break;
						}
						else
						{
							break;
						}
					}
				}
				while (iRecvSize < PACKET_HEADER_SIZE);

				if (iRecvSize == SOCKET_ERROR)
				{
					if (RecvIter != UserList.end())
					{
						RecvIter++;
					}
					continue;
				}

				memcpy(&recvPacket.ph, szRecvBuffer, PACKET_HEADER_SIZE);
				// 데이터 받기
				iRecvSize = 0;
				do {
					int iRecvByte = recv(user.m_Socket, recvPacket.msg,
						recvPacket.ph.len - PACKET_HEADER_SIZE - iRecvSize, 0);
					iRecvSize += iRecvByte;
					if (iRecvByte == 0)
					{
						closesocket(user.m_Socket);
						RecvIter = UserList.erase(RecvIter);
						std::cout << user.m_Name << " 접속종료됨." << std::endl;
						continue;
					}
					if (iRecvByte == SOCKET_ERROR)
					{
						int iError = WSAGetLastError();
						if (iError != WSAEWOULDBLOCK)
						{
							RecvIter = UserList.erase(RecvIter);
							std::cout << user.m_Name << " 비정상 접속종료됨." << std::endl;
						}
						else
						{
							break;
						}
					}
				} while (iRecvSize < recvPacket.ph.len - PACKET_HEADER_SIZE);

				Packet data;
				data.m_uPacket = recvPacket;
				TChatMsg recvdata;
				ZeroMemory(&recvdata, sizeof(recvdata));
				data >> recvdata.index >> recvdata.name
					>> recvdata.damage >> recvdata.message;

				std::cout << "\n" <<
					"[" << recvdata.name << "]"
					<< recvdata.message;

				// 패킷 완성		
				std::list<User>::iterator iterSend;
				for (iterSend = UserList.begin();
					iterSend != UserList.end(); )
				{
					User user = *iterSend;
					int iSendMsgSize = SendMsg(user.m_Socket, recvPacket);
					if (iSendMsgSize < 0)
					{
						closesocket(user.m_Socket);
						iterSend = UserList.erase(iterSend);
						std::cout << user.m_Name << " 비정상 접속종료됨." << std::endl;
					}
					else
					{
						iterSend++;
					}
				}
				if (RecvIter != UserList.end())
				{
					RecvIter++;
				}
			}
		}
	}
	closesocket(sock);
	WSACleanup();
}