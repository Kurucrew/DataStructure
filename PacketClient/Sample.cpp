#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include <iostream>
#include <winsock2.h>
#include <conio.h>
#include "Packet.h"
#pragma comment	(lib, "ws2_32.lib")
using namespace std;

void main()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return;
	}
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
	SOCKADDR_IN SA;
	ZeroMemory(&SA, sizeof(SA));
	SA.sin_family = AF_INET;
	SA.sin_port = htons(10000);
	SA.sin_addr.s_addr = inet_addr("192.168.0.40");
	int Ret = connect(sock, (sockaddr*)&SA, sizeof(SA));
	if (Ret == SOCKET_ERROR) return;
	cout << "접속성공!" << std::endl;
	u_long on = 1;
	ioctlsocket(sock, FIONBIO, &on);
	char szBuffer[256] = { 0, };
	int End = 0;
	while (1)
	{
		if (_kbhit() == 1)
		{
			int Value = _getche();
			if (Value == '\r' && strlen(szBuffer) == 0)
			{
				break;
			}
			if (Value == '\r')
			{
				int SendByte = send(sock, szBuffer, End, 0);
				if (SendByte == SOCKET_ERROR)
				{
					if (WSAGetLastError() != WSAEWOULDBLOCK)
					{
						break;
					}
				}
				End = 0;
				ZeroMemory(szBuffer, sizeof(char) * 256);
			}
			else
			{
				szBuffer[End++] = Value;
			}
		}
		else
		{
			char szRecvBuffer[256] = { 0, };
			int RecvByte = recv(sock, szRecvBuffer, sizeof(szRecvBuffer), 0);
			if (RecvByte == 0)
			{
				cout << "서버 종료" << endl;
				break;
			}
			if (RecvByte == SOCKET_ERROR)
			{
				if (WSAGetLastError() != WSAEWOULDBLOCK)
				{
					cout << "서버 비정상 종료" << endl;
					break;
				}
			}
			else
			{
				cout << szRecvBuffer << endl;
			}
		}
	}
	cout << "접속 죵료" << endl;
	closesocket(sock);
	WSACleanup();
	_getch();
}