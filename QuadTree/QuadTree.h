#pragma once
#include "Node.h"
class QuadTree
{
public:
	int m_Width;
	int m_Height;
	int m_MaxDepth;
	Node* m_Root;
	vector<Node*> g_Array;
	queue<Node*> g_Queue;
	int g_val = 0;
	//Node* g_pArray[7];
	void Init(int width, int height, int maxdepth);
	Node* Create(Node* Parent, float x, float y, float w, float h);
	void Buildtree(Node* Parent);
	bool Addobject(int fx, int fy);
	Node* Findnode(Node* node, int x, int y);
	void PrintList(Node* node);
};

