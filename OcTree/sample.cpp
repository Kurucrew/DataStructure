#include "OcTree.h"

void main()
{
	OcTree tree;
	tree.Init(100, 100, 100, 2);
	for (int i = 0; i < 10; i++)
	{
		Object* obj = new Object();
		obj->SetPos((float)(rand() % 100), (float)(rand() % 100), (float)(rand() % 100));
		float hw = (float)(rand() % 5) + 1;
		float hh = (float)(rand() % 5) + 1;
		float hl = (float)(rand() % 5) + 1;
		Vector3D vec;
		vec.x = obj->m_Pos.x - hw;
		vec.y = obj->m_Pos.y - hh;
		vec.z = obj->m_Pos.z - hl;
		Box bx(vec, hw * 2.0f, hh * 2.0f, hl * 2.0f);
		obj->SetBox(bx);
		tree.Addobject(obj);
	}
	tree.PrintList(tree.m_Root);
}