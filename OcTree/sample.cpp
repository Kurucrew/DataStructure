#include "OcTree.h"

void main()
{
	OcTree tree;
	tree.Init(100, 100, 100, 2);
	for (int i = 0; i < 10; i++)
	{
		int x = rand() % 100;
		int y = rand() % 100;
		int z = rand() % 100;
		tree.Addobject(x, y, z);
	}
	tree.PrintList(tree.m_Root);
}