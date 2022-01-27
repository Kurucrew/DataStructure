#include "Manager.h"

DWORD WINAPI RecvThread(LPVOID param)
{
	Manager* mgr = (Manager*)param;
	while (1)
	{
		WaitForSingleObject(mgr->m_Mutex, INFINITE);

		list<NetUser>::iterator userIter;
		for (userIter = mgr->UserList.begin();
			userIter != mgr->UserList.end();)
		{
			int iRet = mgr->RecvUser(*userIter);
			if (iRet <= 0)
			{
					for (NetUser& send : mgr->UserList)
					{
						mgr->LogoutMsg(send, *userIter);
					}
				userIter = mgr->UserList.erase(userIter);
			}
			else
			{
				userIter++;
			}
		}
		ReleaseMutex(mgr->m_Mutex);
	}
}
DWORD WINAPI SendThread(LPVOID param)
{
	Manager* mgr = (Manager*)param;
	while (1)
	{
		WaitForSingleObject(mgr->m_Mutex, INFINITE);
		list<NetUser>::iterator userIter;
		for (userIter = mgr->UserList.begin();
			userIter != mgr->UserList.end();)
		{
			int iRet = mgr->Broadcast(*userIter);
			if (iRet <= 0)
			{
				userIter = mgr->UserList.erase(userIter);
			}
			else
			{
				userIter++;
			}
		}

		ReleaseMutex(mgr->m_Mutex);

	}
}

int main()
{
	Manager mgr;
	mgr.m_Mutex = CreateMutex(NULL, FALSE, NULL);
	Network Net;
	Net.InitNetwork();
	Net.InitServer(SOCK_STREAM, 10000, 1);
	cout << "서버 가동" << endl;

	DWORD RecvThreadId;
	DWORD SendThreadId;

	HANDLE RecvThreadHandle = ::CreateThread(0, 0, RecvThread, (LPVOID)&mgr, 0, &RecvThreadId);
	CloseHandle(RecvThreadHandle);
	HANDLE SendThreadHandle = ::CreateThread(0, 0, SendThread, (LPVOID)&mgr, 0, &SendThreadId);
	CloseHandle(SendThreadHandle);
	
	while (1)
	{
			mgr.AddUser(Net.m_netSock);

	}
}