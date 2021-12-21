#pragma once
#include <iostream>
class Object
{
public:
	int m_x;
	int m_y;
	Object(int x, int y);
	~Object();


};

Object::Object(int x, int y)
{
	m_x = x;
	m_y = y;
}

Object::~Object()
{
}