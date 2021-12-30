#pragma once
#include <iostream>
#include "Collision.h"
class Object
{
public:
	Vector3D m_Pos;
	Box m_box;
	Object(int x, int y, int z)
	{
		m_Pos.x = x;
		m_Pos.y = y;
		m_Pos.z = z;
	}
	Object()
	{
		m_Pos.x = 0;
		m_Pos.y = 0;
		m_Pos.z = 0;
	}
	void   SetPos(float x, float y, float z);
	void   SetBox(Box rt);
	void MoveObj(Vector3D vec);
};
