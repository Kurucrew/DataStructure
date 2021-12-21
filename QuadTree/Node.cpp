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

}