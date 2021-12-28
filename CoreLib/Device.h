#pragma once
#include "Window.h"
class Device :public Window
{
public:
	ID3D11Device* m_pd3dDevice;	
	ID3D11DeviceContext* m_pImmediateContext;
	IDXGISwapChain* m_pSwapChain;	
	ID3D11RenderTargetView* m_pRenderTargetView;

	D3D_FEATURE_LEVEL       m_FeatureLevel;		
	DXGI_SWAP_CHAIN_DESC	m_SwapChainDesc;	
	D3D11_VIEWPORT			m_ViewPort;	

	HRESULT InitDevice();
	virtual bool	CreateDevice();
	virtual bool	CreateRenderTargetView();
	virtual bool	SetViewPort();
	virtual bool	CleapupDevice();

	Device();
	virtual ~Device();
};

