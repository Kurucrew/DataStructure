#include "QuadTree.h"

void main()
{
	QuadTree tree;
	tree.Init(100, 100, 2);
	for (int i = 0; i < 10; i++)
	{
		int x = rand() % 100;
		int y = rand() % 100;
		tree.Addobject(x, y);
	}
	tree.PrintList(tree.m_Root);
}