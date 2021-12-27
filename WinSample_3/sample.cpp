#include "Window.h"
int WINAPI wWinMain(HINSTANCE hinstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	Window win;
	if (win.WinRegisterClass(hinstance) == FALSE) return 1;
	if (win.SetWindow(L"Sample") == FALSE) return 1;
	win.WinRun();
	return 1;
}