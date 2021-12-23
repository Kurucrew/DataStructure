#pragma once
#include "Node.h"
class OcTree
{
public:
	int m_Width;
	int m_Height;
	int m_Length;
	int m_MaxDepth;
	Node* m_Root;
	vector<Node*> g_Array;
	queue<Node*> g_Queue;
	int g_val = 0;
	//Node* g_pArray[7];
	void Init(int width, int height,int Length, int maxdepth);
	Node* Create(Node* Parent, float x, float y, float z, float w, float h, float l);
	void Buildtree(Node* Parent);
	bool Addobject(int fx, int fy, int fz);
	Node* Findnode(Node* node, int x, int y, int z);
	void PrintList(Node* node);
};

