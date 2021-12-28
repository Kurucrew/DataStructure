#pragma once
#include "std.h"
#include <d3dcompiler.h>
#pragma comment (lib, "d3dcompiler.lib")
struct TestVertex
{
	Vector2D v;
};
class DxObject
{
	float m_Speed;
	Vector2D m_Pos;
	vector<TestVertex> m_InitScreenList;
	vector<TestVertex> m_VertexList;
	ID3D11Buffer* m_VertexBuffer;
	ID3D11InputLayout* m_VertexLayout;
	ID3D11VertexShader* m_VertexShader;
	ID3D11PixelShader* m_PixelShader;
	ID3D11Device* m_D3DDevice;
	ID3D11DeviceContext* m_Context;
public:
	void SetDevice(ID3D11Device* D3DDevice, ID3D11DeviceContext* Context);
	bool Create(ID3D11Device* D3DDevice, ID3D11DeviceContext* Context, Vector2D pos, float width, float height);
	void Convert(Vector2D center, float cwidth, float cheight, vector<TestVertex>& List);
	void Convert(vector<TestVertex>& list, vector<TestVertex>& List);
	virtual bool	Init();
	virtual bool	Frame();
	virtual bool	Render();
	virtual bool	Release();
	DxObject();
	~DxObject();
};

