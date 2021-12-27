#pragma once
#include <vector>//���Ҵ� ������ �迭
#include <queue>
#include <list>
#include"Object.h"
#include"ObjShape.h"
using namespace std;
template <class T>
class Node
{
public:
		int m_Depth;
		Node<T>* m_Parent;
		Box m_Box;
		Node<T>* m_Child[8];
		list<Object*> m_objectList;
		void Addobject(Object* obj);
		bool IsBox(int x, int y, int z);
		Node();
		Node(float x, float y, float z, float w, float h, float l);
		~Node();

};

