#pragma once
#include <vector>//재할당 가능한 배열
#include <queue>
#include <list>
#include"Object.h"
using namespace std;
struct Rect
{
	Vector3D p1;
	Vector3D p2;
	Vector3D mp;
	Vector3D size;
};
class Node
{
public:
		int m_Depth;
		Node* m_Parent;
		Rect m_rt;
		Node* m_Child[8];
		list<Object*> m_objectList;
		void Addobject(int x, int y, int z);
		bool Isrect(int x, int y, int z);
		Node();
		Node(float x, float y, float z, float w, float h, float l);
		~Node();

};

