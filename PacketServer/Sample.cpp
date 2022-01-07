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
{//1.��Ŷ ����
	UPACKET packet;
	ZeroMemory(&packet, sizeof(packet));
	packet.ph.len = strlen(msg) + PACKET_HEADER_SIZE;
	packet.ph.type = type;
	memcpy(packet.msg, msg, strlen(msg));
	//2.��Ŷ ����
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
	//1.���� ȯ�漳�� �� Ȱ��ȭ
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return;
	}
	//2.���� ����
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN SA;
	ZeroMemory(&SA, sizeof(SA));
	SA.sin_family = AF_INET;
	SA.sin_port = htons(10000);
	SA.sin_addr.s_addr = htonl(INADDR_ANY);//������ ��� ip�� �޴� ��ũ��
	//3.���ε�
	int RetB = bind(sock, (sockaddr*)&SA, sizeof(SA));
	if (RetB == SOCKET_ERROR) return;
	//4.������
	RetB = listen(sock, SOMAXCONN);
	if (RetB == SOCKET_ERROR) return;
	//5.�����
	SOCKADDR_IN clientAddr;
	int Len = sizeof(clientAddr);
	cout << "���� ����" << endl;
	u_long on = 1;
	ioctlsocket(sock, FIONBIO, &on);
	list<User> UserList;
	while (1)
	{
		//������ ������ üũ
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
			//������ ������ �ִ°�� ��������Ʈ�� �߰�
			User user;
			user.set(clientSock, clientAddr);
			UserList.push_back(user);
			cout << "ip : " << user.m_Name << " port : " << user.m_Port << endl;
			cout << UserList.size() << "�� ����" << endl;
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
						cout << "ip : " << user.m_Name << " port : " << user.m_Port << " | ���� ����" << endl;
						closesocket(user.m_Socket);
						RecvIter = UserList.erase(RecvIter);//������ ������ �����ϸ� ��������Ʈ���� ����
						cout << UserList.size() << "�� ����" << endl;
						break;
					}
					if (RecvByte == SOCKET_ERROR)
					{
						int iError = WSAGetLastError();
						if (iError != WSAEWOULDBLOCK)
						{
							RecvIter = UserList.erase(RecvIter);
							cout << "ip : " << user.m_Name << " port : " << user.m_Port << " | ������ ���� ����" << endl;
							cout << UserList.size() << "�� ����" << endl;
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
				// ������ �ޱ�
				iRecvSize = 0;
				do {
					int iRecvByte = recv(user.m_Socket, recvPacket.msg,
						recvPacket.ph.len - PACKET_HEADER_SIZE - iRecvSize, 0);
					iRecvSize += iRecvByte;
					if (iRecvByte == 0)
					{
						closesocket(user.m_Socket);
						RecvIter = UserList.erase(RecvIter);
						std::cout << user.m_Name << " ���������." << std::endl;
						continue;
					}
					if (iRecvByte == SOCKET_ERROR)
					{
						int iError = WSAGetLastError();
						if (iError != WSAEWOULDBLOCK)
						{
							RecvIter = UserList.erase(RecvIter);
							std::cout << user.m_Name << " ������ ���������." << std::endl;
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

				// ��Ŷ �ϼ�		
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
						std::cout << user.m_Name << " ������ ���������." << std::endl;
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