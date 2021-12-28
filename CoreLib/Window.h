#pragma once
#include "std.h"
class Window
{
public:
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	RECT m_Client;
	RECT m_Window;

	BOOL  SetWinClass(HINSTANCE hInstance);
	BOOL  SetWindow(const WCHAR* szTitle = L"Sample",
		int iWidth = 800,
		int iHeight = 600);
	bool  WinRun();
	Window();
	virtual ~Window();
};

