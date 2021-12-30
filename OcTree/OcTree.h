#pragma once
#include "Node.cpp"
class OcTree
{
public:
	int m_Width;
	int m_Height;
	int m_Length;
	int m_MaxDepth;
	static int m_NodeCounter;
	Node<Box>* m_Root;
	queue<Node<Box>*> g_Queue;
	int g_val = 0;
	void Init(int width, int height,int Length, int maxdepth);
	Node<Box>* Create(Node<Box>* Parent, float x, float y, float z, float w, float h, float l);
	void Buildtree(Node<Box>* Parent);
	bool Addobject(Object* obj);
	bool AddDobject(Object* obj);
	void DelDobject(Node<Box>* node);
	Node<Box>* Findnode(Node<Box>* node, Box bx);
	void PrintList(Node<Box>* node);
	void PrintDObjList(Node<Box>* node);
};

