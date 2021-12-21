#pragma once
#include "Node.h"
class QuadTree
{
public:
	vector<TNode>
	void BinaryNodePrintPreOrder(Node* pNode);
	void BinaryNodePrintInOrder(Node* pNode);
	void BinaryNodePrintPostOrder(Node* pNode);
	void BinaryNodePrintLevelOrder(Node* pNode);
	void CreaeBinaryNode(Node* pNode);
	Node* g_pArray[7];
	std::queue<Node*> g_Queue;
	int g_iValue = 0;
};

