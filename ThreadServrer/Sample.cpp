#include "Manager.h"

int main()
{
	Manager mgr;
	Network Net;
	Net.InitNetwork();
	Net.InitServer(SOCK_STREAM, 10000);
	cout << "���� ����" << endl;

	while (1)
	{
	}
}