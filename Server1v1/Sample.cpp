#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<iostream>
#include<winsock2.h>
#pragma comment (lib, "ws2_32.lib")
using namespace std;
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
	while (1)
	{
		SOCKADDR_IN clientAddr;
		int Len = sizeof(clientAddr);
		SOCKET clientSock = accept(sock, (sockaddr*)&clientAddr, &Len);
		cout << "ip : " << inet_ntoa(clientAddr.sin_addr) << " port : " << ntohs(clientAddr.sin_port) << endl;
		char szRecvBuffer[256] = { 0, };
		int RecvByte = recv(clientSock, szRecvBuffer, sizeof(szRecvBuffer), 0);
		if (RecvByte == 0)
		{
			cout << "ip : " << inet_ntoa(clientAddr.sin_addr) << " port : " << ntohs(clientAddr.sin_port) << endl;
			closesocket(clientSock);
		}
		int SendByte = send(clientSock, szRecvBuffer, sizeof(RecvByte), 0);
	}
	WSACleanup();
}