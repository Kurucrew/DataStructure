#include "Core.h"
bool Core::CoreInit()
{
	CreateDevice();
	Init();
	return true;
}
bool Core::CoreFrame()
{
	Frame();
	return true;
}
bool Core::CoreRender()
{
	float color[4] = { 0.255f, 0.255f, 0.255f, 1.0f };
	m_pImmediateContext->ClearRenderTargetView(m_pRenderTargetView, color);
	Render();
	m_pSwapChain->Present(0, 0);
	return true;
}
bool Core::CoreRelease()
{
	Release();
	CleapupDevice();
	return true;
}
bool Core::GameRun()
{
	CoreInit();
	while (WinRun())
	{
		CoreFrame();
		CoreRender();
	}
	CoreRelease();
	return true;
}