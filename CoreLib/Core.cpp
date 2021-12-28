#include "Core.h"
bool Core::CoreInit()
{
	InitDevice();
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
	float color[4] = { 0.2f, 0.13f, 0.22f, 1.0f };
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
Core::Core()
{

}
Core::~Core()
{

}