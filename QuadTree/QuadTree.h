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
	
};

