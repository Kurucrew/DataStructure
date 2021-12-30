#include "Node.h"
//template <class T>
//bool Node<T>::IsBox(int x, int y, int z)
//{
//	if (m_Box.p1.x <= x && m_Box.p2.x >= x && m_Box.p1.y <= y && m_Box.p2.y >= y && m_Box.p1.z <= y && m_Box.p2.z >= y)
//	{
//		return true;
//	}
//	return false;
//}
template <class T>
void Node<T>::Addobject(Object* obj)
{
	m_objectList.push_back(obj);
}
template <class T>
void Node<T>::AddDobject(Object* obj)
{
	m_DobjectList.push_back(obj);
}
template <class T>
Node<T>::Node()
{
	m_Parent = nullptr;
	m_Depth = 0;
	m_Child[0] = nullptr;
	m_Child[1] = nullptr;
	m_Child[2] = nullptr;
	m_Child[3] = nullptr;
	m_Child[4] = nullptr;
	m_Child[5] = nullptr;
	m_Child[6] = nullptr;
	m_Child[7] = nullptr;
	for (list<Object*>::iterator iter = m_objectList.begin(); iter != m_objectList.end(); iter++)
	{
		Object* obj = *iter;
		delete obj;
	}
	m_objectList.clear();
}
template <class T>
Node<T>::Node(float x, float y, float z, float w, float h, float l) : Node()
{
	m_Box.p1.x = x;
	m_Box.p1.y = y;
	m_Box.p1.z = z;
	m_Box.p2.x = x + w;
	m_Box.p2.y = y + h;
	m_Box.p2.z = z + l;
	m_Box.mp.x = x + (w / 2.0f);
	m_Box.mp.y = y + (h / 2.0f);
	m_Box.mp.z = z + (l / 2.0f);
	m_Box.size.x = w;
	m_Box.size.y = h;
	m_Box.size.z = l;
	m_Child[0] = nullptr;
	m_Child[1] = nullptr;
	m_Child[2] = nullptr;
	m_Child[3] = nullptr;
	m_Child[4] = nullptr;
	m_Child[5] = nullptr;
	m_Child[6] = nullptr;
	m_Child[7] = nullptr;
}
template <class T>
Node<T>::~Node()
{
	delete m_Child[0];
	delete m_Child[1];
	delete m_Child[2];
	delete m_Child[3];
	delete m_Child[4];
	delete m_Child[5];
	delete m_Child[6];
	delete m_Child[7];
}