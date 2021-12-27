#pragma once
#include <Windows.h>
class Window
{
public:
	HINSTANCE	m_hInstance;
	HWND		m_hWnd;
	RECT		m_rtClient;
	RECT		m_rtWindow;
public:
	BOOL  WinRegisterClass(HINSTANCE hInstance);
	BOOL  SetWindow(const WCHAR* szTitle = L"Sample",
		int iWidth = 1024,
		int iHeight = 768);
	bool  WinRun();
};

