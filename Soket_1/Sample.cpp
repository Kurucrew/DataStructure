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
	SOCKET sock = socket(AF_INET,SOCK_STREAM, 0);//3번째 인수는 2번째인수에 의해 자동으로 결정되기 때문에 0을 집어넣어도 된다
	/*sockaddr SA;
	SA.sa_family = AF_INET;
	CHAR sa_data[14];*/
	SOCKADDR_IN SA;
	ZeroMemory(&SA, sizeof(SA));
	SA.sin_family = AF_INET;
	SA.sin_port = htons(10000);//호스트바이트를 네트워크바이트 쇼트로 바꿔주는 함수
	SA.sin_addr.s_addr = inet_addr("192.168.0.12");//ip주소를 바이트로 변환해주는 함수
	int Ret = connect(sock, (sockaddr*)&SA, sizeof(SA));
	char szBuffer[] = "hello";
	int SendByte = send(sock, szBuffer, sizeof(szBuffer), 0);
	char szRecvBuffer[256] = { 0, };
	int RecvByte = recv(sock, szRecvBuffer, 256, 0);//서버에 보내자마자 다시받는 에코시스템
	cout << RecvByte << endl;
	WSACleanup();
}