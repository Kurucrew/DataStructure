#include "Node.h"

bool Node::Isrect(int x, int y)
{
	if (m_rt.x1 <= x && m_rt.x2 >= x && m_rt.y1 <= y && m_rt.y2 >= y)
	{
		return true;
	}
	return false;
}
void Node::Addobject(int x, int y)
{
	m_objectList.push_back(new Object(x, y));
}
Node::Node()
{
	m_Parent = nullptr;
	m_Depth = 0;
	m_Child[0] = nullptr;
	m_Child[1] = nullptr;
	m_Child[2] = nullptr;
	m_Child[3] = nullptr;
	for (list<Object*>::iterator iter = m_objectList.begin(); iter != m_objectList.end(); iter++)
	{
		Object* obj = *iter;
		delete obj;
	}
	m_objectList.clear();
}
Node::Node(float x, float y, float w, float h) : Node()
{
	m_rt.x1 = x;
	m_rt.y1 = y;
	m_rt.x2 = x + w;
	m_rt.y2 = y + h;
	m_rt.mx = x + (w / 2.0f);
	m_rt.my = y + (h / 2.0f);
	m_rt.w = w;
	m_rt.h = h;
	m_Child[0] = nullptr;
	m_Child[1] = nullptr;
	m_Child[2] = nullptr;
	m_Child[3] = nullptr;
}
Node::~Node()
{
	delete m_Child[0];
	delete m_Child[1];
	delete m_Child[2];
	delete m_Child[3];
}