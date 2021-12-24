#include "OcTree.h"
Node* OcTree::Create(Node* Parent, float x, float y, float z, float w, float h, float l)
{
	Node* node = new Node(x, y, z, w, h, l);
	if (Parent != nullptr)
	{
		node->m_Depth = Parent->m_Depth + 1;
	}
	return node;
}
void OcTree::Init(int Width, int Height, int Length, int Maxdepth)
{
	m_MaxDepth = Maxdepth;
	m_Width = Width;
	m_Height = Height;
	m_Length = Length;
	m_Root = Create(nullptr, 0, 0, 0, m_Width, m_Height, m_Length);
	Buildtree(m_Root);
}
void OcTree::Buildtree(Node* parent)
{
	if (parent->m_Depth == m_MaxDepth)
		return;
	float fz = parent->m_Box.p1.z;
	float SizeX = parent->m_Box.size.x / 2.0f;
	float SizeY = parent->m_Box.size.y / 2.0f;
	float SizeZ = parent->m_Box.size.z / 2.0f;
	int num = 0;
	for (int i = 0; i < 2; i++)
	{
		parent->m_Child[num] = Create(parent, parent->m_Box.p1.x, parent->m_Box.p1.y, fz, SizeX , SizeY , SizeZ );
		Buildtree(parent->m_Child[num++]);
		parent->m_Child[num] = Create(parent, parent->m_Box.mp.x, parent->m_Box.p1.y, fz, SizeX , SizeY , SizeZ );
		Buildtree(parent->m_Child[num++]);
		parent->m_Child[num] = Create(parent, parent->m_Box.mp.x, parent->m_Box.mp.y, fz, SizeX , SizeY , SizeZ );
		Buildtree(parent->m_Child[num++]);
		parent->m_Child[num] = Create(parent, parent->m_Box.p1.x, parent->m_Box.mp.y, fz, SizeX , SizeY , SizeZ );
		Buildtree(parent->m_Child[num++]);
		fz = parent->m_Box.mp.z;
	}
}
bool OcTree::Addobject(int fx, int fy, int fz)
{
	Node* fNode = Findnode(m_Root, fx, fy, fz);
	if (fNode != nullptr)
	{
		fNode->Addobject(fx, fy, fz);
		return true;
	}
	return false;
}
Node* OcTree::Findnode(Node* node, int x, int y, int z)
{
	do {
		for (int i = 0; i < 8; i++)
		{
			if (node->m_Child[i] != nullptr)
			{
				if (node->m_Child[i]->IsBox(x, y ,z))
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
void OcTree::PrintList(Node* node)
{
	if (node == nullptr) return;
	for (list<Object*>::iterator iter = node->m_objectList.begin(); iter != node->m_objectList.end(); iter++)
	{
		Object* obj = *iter;
		cout << "[" << node->m_Depth << "]" << obj->m_Pos.x << ":" << obj->m_Pos.y << ":" << obj->m_Pos.z;
	}
	cout << endl;
	for (int i = 0; i < 8; i++)
	{
		PrintList(node->m_Child[i]);
	}
}