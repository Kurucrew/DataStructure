#pragma once
#include <vector>//재할당 가능한 배열
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
		int m_Index;
		Node<T>* m_Parent;
		Box m_Box;
		Node<T>* m_Child[8];
		list<Object*> m_objectList;
		list<Object*> m_DobjectList;
		void Addobject(Object* obj);
		void AddDobject(Object* obj);
		//bool IsBox(int x, int y, int z);
		Node();
		Node(float x, float y, float z, float w, float h, float l);
		~Node();

};

