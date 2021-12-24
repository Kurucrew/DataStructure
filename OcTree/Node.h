#pragma once
#include <vector>//재할당 가능한 배열
#include <queue>
#include <list>
#include"Object.h"
#include"ObjShape.h"
using namespace std;
class Node
{
public:
		int m_Depth;
		Node* m_Parent;
		Box m_Box;
		Node* m_Child[8];
		list<Object*> m_objectList;
		void Addobject(int x, int y, int z);
		bool IsBox(int x, int y, int z);
		Node();
		Node(float x, float y, float z, float w, float h, float l);
		~Node();

};

