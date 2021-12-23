#include "QuadTree.h"
Node* QuadTree::Create(Node* Parent, float x, float y, float w, float h)
{
	Node* node = new Node(x, y, w, h);
	if (Parent != nullptr)
	{
		node->m_Depth = Parent->m_Depth + 1;
	}
	return node;
}
void QuadTree::Init(int Width, int Height, int Maxdepth)
{
	m_MaxDepth = Maxdepth;
	m_Width = Width;
	m_Height = Height;
	m_Root = Create(nullptr, 0, 0, m_Width, m_Height);
	Buildtree(m_Root);
}
void QuadTree::Buildtree(Node* parent)
{
	if (parent->m_Depth == m_MaxDepth)
		return;
	parent->m_Child[0] = Create(parent, parent->m_rt.p1.x, parent->m_rt.p1.y, parent->m_rt.size.x / 2.0f, parent->m_rt.size.y / 2.0f);
	Buildtree(parent->m_Child[0]);
	parent->m_Child[1] = Create(parent, parent->m_rt.mp.x, parent->m_rt.p1.y, parent->m_rt.size.x / 2.0f, parent->m_rt.size.y / 2.0f);
	Buildtree(parent->m_Child[1]);
	parent->m_Child[2] = Create(parent, parent->m_rt.mp.x, parent->m_rt.mp.y, parent->m_rt.size.x / 2.0f, parent->m_rt.size.y / 2.0f);
	Buildtree(parent->m_Child[2]);
	parent->m_Child[3] = Create(parent, parent->m_rt.p1.x, parent->m_rt.mp.y, parent->m_rt.size.x / 2.0f, parent->m_rt.size.y / 2.0f);
	Buildtree(parent->m_Child[3]);
}
bool QuadTree::Addobject(int fx, int fy)
{
	Node* fNode = Findnode(m_Root, fx, fy);
	if (fNode != nullptr)
	{
		fNode->Addobject(fx, fy);
		return true;
	}
	return false;
}
Node* QuadTree::Findnode(Node* node, int x, int y)
{
	do {
		for (int i = 0; i < 4; i++)
		{
			if (node->m_Child[i] != nullptr)
			{
				if (node->m_Child[i]->Isrect(x, y))
				{
					g_Queue.push(node->m_Child[i]);
					break;
				}
			}
		}
		if (g_Queue.empty()) break;
		node = g_Queue.front();
		g_Queue.pop();
	} while (node);
	return node;
}
void QuadTree::PrintList(Node* node)
{
	if (node == nullptr) return;
	for (list<Object*>::iterator iter = node->m_objectList.begin(); iter != node->m_objectList.end(); iter++)
	{
		Object* obj = *iter;
		cout << "[" << node->m_Depth << "]" << obj->m_Pos.x << ":" << obj->m_Pos.y << endl;
	}
	for (int i = 0; i < 4; i++)
	{
		PrintList(node->m_Child[i]);
	}
}