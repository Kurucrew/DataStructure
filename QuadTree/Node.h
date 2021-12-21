#pragma once
#include <iostream>
#include <vector>//재할당 가능한 배열
#include <queue>
#include <list>
#include"Object.h"
using namespace std;
struct Rect
{
	float x1, y1;
	float x2, y2;
	float mx, my;
	float w, h;
};
class Node
{
public:
		int m_Depth;
		Node* m_Parent;
		Rect m_rt;
		Node* m_Child[4];
		list<Object*> m_objectList;
		void Addobject(int x, int y);
		bool Isrect(int x, int y);
		Node();
		Node(float x, float y, float w, float h);
		~Node();

};

