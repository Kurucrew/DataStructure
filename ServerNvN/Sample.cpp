#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<iostream>
#include<winsock2.h>
#include <list>
#include <string>
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
				User user;
				user = *RecvIter;
				char szRecvBuffer[256] = { 0, };
				int RecvByte = recv(user.m_Socket, szRecvBuffer, sizeof(szRecvBuffer), 0);
				if (RecvByte == 0)
				{
					cout << "ip : " << user.m_Name << " port : " << user.m_Port << " | ���� ����" << endl;
					closesocket(user.m_Socket);
					RecvIter = UserList.erase(RecvIter);//������ ������ �����ϸ� ��������Ʈ���� ����
					cout << UserList.size() << "�� ����" << endl;
					continue;
				}
				if (RecvByte == SOCKET_ERROR)
				{
					int iError = WSAGetLastError();
					if (iError != WSAEWOULDBLOCK)
					{
						RecvIter = UserList.erase(RecvIter);
						cout << "ip : " << user.m_Name << " port : " << user.m_Port << " | ������ ���� ����" << endl;
						cout << UserList.size() << "�� ����" << endl;
					}
					else
					{
						RecvIter++;
					}
				}
				else
				{//���� �����͸� �޾����� ������ ��� �������� ����
					list<User>::iterator SendIter;
					for (SendIter = UserList.begin(); SendIter != UserList.end();)
					{
						User user = *SendIter;
						cout << szRecvBuffer << " : ����" << endl;
						int SendByte = send(user.m_Socket, szRecvBuffer, RecvByte, 0);
						cout << user.m_Socket << ":" << SendByte << " : ����" << ::endl;
						SendIter++;
					}
				}
			}
		}
	}
	closesocket(sock);
	WSACleanup();
}