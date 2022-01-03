#define _WINSOCK_DEPRECATED_NO_WARNINGS
#include<iostream>
#include<winsock2.h>
#include <conio.h>
#pragma comment (lib, "ws2_32.lib")
using namespace std;
void main()
{
	//1.소켓 환경설정 및 활성화
	WSADATA wsa;
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		return;
	}
	//2.소켓 생성
	SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);//3번째 인수는 2번째인수에 의해 자동으로 결정되기 때문에 0을 집어넣어도 된다
	/*sockaddr SA;
	SA.sa_family = AF_INET;
	CHAR sa_data[14];*/
	SOCKADDR_IN SA;
	ZeroMemory(&SA, sizeof(SA));
	SA.sin_family = AF_INET;
	SA.sin_port = htons(10000);//호스트바이트를 네트워크바이트 쇼트로 바꿔주는 함수
	SA.sin_addr.s_addr = inet_addr("192.168.0.40");//ip주소를 바이트로 변환해주는 함수
	//3.서버와 연결
	int Ret = connect(sock, (sockaddr*)&SA, sizeof(SA));
	if (Ret == SOCKET_ERROR) return;
	cout << "접속성공!" << std::endl;
	u_long on = 1;
	ioctlsocket(sock, FIONBIO, &on);
	char szBuffer[256] = {0, };
	int End = 0;
	while (1)
	{
		if (_kbhit() == 1)
		{
			int Value = _getche();
			if (Value == '\r')//문자가 입력되었는지 감지
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
			}
			else
			{
				szBuffer[End++] = Value;
			}
		}
		else
		{
			char szRecvBuffer[256] = {0, };
			int RecvByte = recv(sock, szRecvBuffer, sizeof(szRecvBuffer), 0);//서버에 보내자마자 다시받는 에코시스템
			if (RecvByte == 0)
			{
				cout << "서버 종료" << endl;
				break;
			}
			if (RecvByte == SOCKET_ERROR)
			{
				if(WSAGetLastError() != WSAEWOULDBLOCK)
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