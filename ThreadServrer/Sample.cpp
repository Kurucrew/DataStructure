#include "Manager.h"

int main()
{
	Manager mgr;
	Network Net;
	Net.InitNetwork();
	Net.InitServer(SOCK_STREAM, 10000);
	cout << "서버 가동" << endl;

	while (1)
	{
	}
}