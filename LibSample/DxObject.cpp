#include "DxObject.h"
void DxObject::SetDevice(ID3D11Device* D3DDevice, ID3D11DeviceContext* Context)
{
	m_D3DDevice = D3DDevice;
	m_Context = Context;
}
bool DxObject::Create(ID3D11Device* D3DDevice, ID3D11DeviceContext* Context, Vector2D pos, float width, float height)
{
	SetDevice(D3DDevice, Context);
	HRESULT hr;
	m_Pos = pos;
	Convert(m_Pos, width, height, m_VertexList);
	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
	bd.ByteWidth = sizeof(TestVertex) * m_VertexList.size();
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(D3D11_SUBRESOURCE_DATA));
	sd.pSysMem = &m_VertexList.at(0);

	if (FAILED(hr = m_D3DDevice->CreateBuffer(&bd, &sd, &m_VertexBuffer)))
	{
		return false;
	}

	ID3DBlob* VSResult = nullptr;
	ID3DBlob* ErrMsg = nullptr;
	hr = D3DCompileFromFile(L"VertexShader.txt", NULL, NULL, "VS", "vs_5_0", 0, 0, &VSResult, &ErrMsg);

	if (FAILED(hr))
	{
		MessageBoxA(NULL, (char*)ErrMsg->GetBufferPointer(), "Error", MB_OK);
		return false;
	}
	hr = m_D3DDevice->CreateVertexShader(VSResult->GetBufferPointer(), VSResult->GetBufferSize(), NULL, &m_VertexShader);
	if (FAILED(hr))
	{
		return false;
	}

	ID3DBlob* PSResult = nullptr;
	hr = D3DCompileFromFile(L"PixelShader.txt", NULL, NULL, "PS", "ps_5_0", 0, 0, &PSResult, &ErrMsg);

	if (FAILED(hr))
	{
		MessageBoxA(NULL, (char*)ErrMsg->GetBufferPointer(), "Error", MB_OK);
		return false;
	}

	hr = m_D3DDevice->CreatePixelShader(PSResult->GetBufferPointer(), PSResult->GetBufferSize(), NULL, &m_PixelShader);

	if (FAILED(hr))
	{
		return false;
	}

	D3D11_INPUT_ELEMENT_DESC layout[] = { 
		{"POSITION", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);
	hr = m_D3DDevice->CreateInputLayout(layout, numElements, VSResult->GetBufferPointer(), VSResult->GetBufferSize(), &m_VertexLayout);

	if (FAILED(hr))
	{
		return false;
	}
	return true;

}
void DxObject::Convert(Vector2D center, float cwidth, float cheight, vector<TestVertex>& List)
{
	vector<TestVertex> list(6);
	float hWidth = cwidth / 2.0f;
	float hHeight = cheight / 2.0f;

	list[0].v = { center.x - hWidth, center.y - hHeight };
	list[1].v = { center.x + hWidth, center.y - hHeight };
	list[2].v = { center.x - hWidth, center.y + hHeight };
	list[3].v = list[2].v;
	list[4].v = list[1].v;
	list[5].v = { center.x + hWidth, center.y + hHeight };

	Convert(list, List);
}
void DxObject::Convert(vector<TestVertex>& list, vector<TestVertex>& List)
{
	List.resize(list.size());
	for (int i = 0; i < list.size(); i++)
	{
		List[i].v.x = list[i].v.x / g_Client.right;
		List[i].v.y = list[i].v.y / g_Client.bottom;
		List[i].v.x = List[i].v.x * 2.0f - 1.0f;
		List[i].v.y = -1.0f * (List[i].v.y * 2.0f - 1.0f);
	}
}
bool DxObject::Init()
{
	return true;
}
bool DxObject::Frame()
{
	m_VertexList[0].v.x += m_Speed;
	m_VertexList[1].v.x += m_Speed;
	m_VertexList[2].v.x += m_Speed;
	m_VertexList[3].v.x += m_Speed;
	m_VertexList[4].v.x += m_Speed;
	m_VertexList[5].v.x += m_Speed;
	m_Context->UpdateSubresource(
		m_VertexBuffer, 0, NULL, &m_VertexList.at(0), 0, 0);
	return true;
}
bool DxObject::Render()
{
	m_Context->IASetInputLayout(m_VertexLayout);
	m_Context->VSSetShader(m_VertexShader, NULL, 0);
	m_Context->PSSetShader(m_PixelShader, NULL, 0);
	UINT StartSlot;
	UINT numBuffers;
	UINT Strides = sizeof(TestVertex);
	UINT Offset = 0;
	m_Context->IASetVertexBuffers(0, 1, &m_VertexBuffer, &Strides, &Offset);
	m_Context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_Context->Draw(m_VertexList.size(), 0);
	return true;
}
bool DxObject::Release()
{
	if (m_VertexBuffer) m_VertexBuffer->Release();
	if (m_VertexLayout) m_VertexLayout->Release();
	if (m_VertexShader) m_VertexShader->Release();
	if (m_PixelShader) m_PixelShader->Release();
	m_VertexBuffer = nullptr;
	m_VertexLayout = nullptr;
	m_VertexShader = nullptr;
	m_PixelShader = nullptr;
	return true;
}
DxObject::DxObject()
{
	m_Speed = 0.00001f;
}
DxObject::~DxObject()
{

}