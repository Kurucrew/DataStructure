#include "QuadTree.h"

void main()
{
	QuadTree tree;
	Node* pRoot = new Node(0);
	tree.g_pArray[0] = pRoot;
	pRoot->iDepth = 0;
	tree.CreaeBinaryNode(pRoot);
	tree.BinaryNodePrintPreOrder(pRoot);
	std::cout << std::endl;
	tree.BinaryNodePrintInOrder(pRoot);
	std::cout << std::endl;
	tree.BinaryNodePrintPostOrder(pRoot);
	std::cout << std::endl;

	tree.g_Queue.push(pRoot);
	tree.BinaryNodePrintLevelOrder(pRoot);

	delete pRoot;
}