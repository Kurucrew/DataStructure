#include "ClientMgr.h"

HANDLE g_hConnectEvent;
//HANDLE g_hExecuteSemaphore;
ClientMgr mgr;

DWORD WINAPI SendThread(LPVOID lpThreadParameter)
{
	Network* net = (Network*)lpThreadParameter;
	char szBuffer[256] = { 0, };

	while (1)
	{
		DWORD dwRet = WaitForSingleObject(g_hConnectEvent, INFINITE);
		if (dwRet != WAIT_OBJECT_0)
		{
			break;
		}
		ZeroMemory(szBuffer, sizeof(char) * 256);
		fgets(szBuffer, 256, stdin);
		if (strlen(szBuffer) == 0)
		{
			std::cout << "���� �����.." << std::endl;
			break;
		}

		int iSendByte = mgr.SendPacket(net->m_netSock, szBuffer, PACKET_CHAT_MSG);
		if (iSendByte < 0)
		{
			std::cout << "������ �����.." << std::endl;
			break;
		}
	}
	return 0;
}
DWORD WINAPI RecvThread(LPVOID param)
{
	Network* net = (Network*)param;
	bool bRun = false;
	while (1)
	{
		DWORD dwRet = WaitForSingleObject(g_hConnectEvent, INFINITE);
		if (dwRet != WAIT_OBJECT_0)
		{
			break;
		}
		UPACKET packet;
		int iRet = mgr.RecvPacketHeader(net->m_netSock, packet);
		if (iRet < 0) continue;
		if (iRet == 1)
		{
			int iRet = mgr.RecvPacketData(net->m_netSock, packet);
			if (iRet < 0) break;
			if (iRet == 0) continue;
			// �޼��� ó��
			Packet data;
			data.m_uPacket = packet;
			TChatMsg recvdata;
			ZeroMemory(&recvdata, sizeof(recvdata));
			if (data.m_uPacket.ph.type == 1100)
			{
				data >> recvdata.message;
				std::cout << "\n" <<
					"[" << recvdata.message << "]";
			}
			else
			{
				data >> recvdata.index >> recvdata.name >> recvdata.damage >> recvdata.message;
				std::cout << "\n" <<
					"[" << recvdata.name << "]" << recvdata.message;
			}
		}
	}
	return 0;
}
void main()
{
	cout << "�̸��� �Է��ϼ��� : ";
	cin >> mgr.UserName;
	g_hConnectEvent =
		CreateEvent(NULL, TRUE, FALSE, NULL);
	/*g_hExecuteSemaphore =
		CreateSemaphore(NULL, 3, 3, L"ExecuteA");*/

	Network net;
	net.InitNetwork();

	DWORD ThreadId;
	HANDLE hThread = ::CreateThread(0,0,SendThread,(LPVOID)&net,0,&ThreadId);
	DWORD ThreadIdRecv;
	HANDLE hThreadRecv = ::CreateThread(0,0,RecvThread,(LPVOID)&net,0,&ThreadIdRecv);

	net.InitServer(SOCK_STREAM,10000,0, "192.168.0.86");
	std::cout << "���Ӽ���!" << std::endl;
	char Buffer[] = " ���� �����߽��ϴ�";
	mgr.SendPacket(net.m_netSock, Buffer, PACKET_CHAT_MSG);

	SetEvent(g_hConnectEvent);

	u_long on = 0;
	ioctlsocket(net.m_netSock, FIONBIO, &on);

	while (1)
	{
		Sleep(1);
	}
	std::cout << "��������" << std::endl;

	CloseHandle(hThread);
	closesocket(net.m_netSock);
	WSACleanup();

	CloseHandle(g_hConnectEvent);
}