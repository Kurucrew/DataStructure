#include "Node.h"

bool Node::Isrect(int x, int y)
{
	if (m_rt.p1.x <= x && m_rt.p2.x >= x && m_rt.p1.y <= y && m_rt.p2.y >= y)
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
	m_rt.p1.x = x;
	m_rt.p1.y = y;
	m_rt.p2.x = x + w;
	m_rt.p2.y = y + h;
	m_rt.mp.x = x + (w / 2.0f);
	m_rt.mp.y = y + (h / 2.0f);
	m_rt.size.x = w;
	m_rt.size.y = h;
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