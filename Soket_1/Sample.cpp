#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<iostream>
#include<winsock2.h>
#pragma comment (lib, "ws2_32.lib")
using namespace std;
void main()
{
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return;
	}
	SOCKET sock = socket(AF_INET,SOCK_STREAM, 0);//3��° �μ��� 2��°�μ��� ���� �ڵ����� �����Ǳ� ������ 0�� ����־ �ȴ�
	/*sockaddr SA;
	SA.sa_family = AF_INET;
	CHAR sa_data[14];*/
	SOCKADDR_IN SA;
	ZeroMemory(&SA, sizeof(SA));
	SA.sin_family = AF_INET;
	SA.sin_port = htons(10000);//ȣ��Ʈ����Ʈ�� ��Ʈ��ũ����Ʈ ��Ʈ�� �ٲ��ִ� �Լ�
	SA.sin_addr.s_addr = inet_addr("192.168.0.12");//ip�ּҸ� ����Ʈ�� ��ȯ���ִ� �Լ�
	int Ret = connect(sock, (sockaddr*)&SA, sizeof(SA));
	char szBuffer[] = "hello";
	int SendByte = send(sock, szBuffer, sizeof(szBuffer), 0);
	char szRecvBuffer[256] = { 0, };
	int RecvByte = recv(sock, szRecvBuffer, 256, 0);//������ �����ڸ��� �ٽù޴� ���ڽý���
	cout << RecvByte << endl;
	WSACleanup();
}