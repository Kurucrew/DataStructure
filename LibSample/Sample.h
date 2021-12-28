#pragma once
#include "Core.h"
#include "DxObject.h"
class Sample : public Core
{
	vector<DxObject> m_ObjList;
public:
	virtual bool	Init()  override;
	virtual bool	Frame()  override;
	virtual bool	Render()  override;
	virtual bool	Release()  override;

	Sample();
	~Sample();
};