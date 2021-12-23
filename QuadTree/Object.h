#pragma once
#include <iostream>
#include "Vector2D.h"
class Object
{
public:
	Vector2D m_Pos;
	Object(int x, int y)
	{
		m_Pos.x = x;
		m_Pos.y = y;
	}


};
