#pragma once
#include <iostream>
#include "Vector3D.h"
class Object
{
public:
	Vector3D m_Pos;
	Object(int x, int y, int z)
	{
		m_Pos.x = x;
		m_Pos.y = y;
		m_Pos.z = z;
	}


};
