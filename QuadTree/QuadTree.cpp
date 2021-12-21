#include "QuadTree.h"
void QuadTree::BinaryNodePrintPreOrder(Node* pNode)
{
	if (pNode == nullptr) return;
	std::cout << pNode->iValue;
	BinaryNodePrintPreOrder(pNode->pLeft);
	BinaryNodePrintPreOrder(pNode->pRight);
}
void QuadTree::BinaryNodePrintInOrder(Node* pNode)
{
	if (pNode == nullptr) return;
	BinaryNodePrintInOrder(pNode->pLeft);
	std::cout << pNode->iValue;
	BinaryNodePrintInOrder(pNode->pRight);
}
void QuadTree::BinaryNodePrintPostOrder(Node* pNode)
{
	if (pNode == nullptr) return;
	BinaryNodePrintPostOrder(pNode->pLeft);
	BinaryNodePrintPostOrder(pNode->pRight);
	std::cout << pNode->iValue;
}

void QuadTree::BinaryNodePrintLevelOrder(Node* pNode)
{
	do {
		if (pNode->pLeft != nullptr)
			g_Queue.push(pNode->pLeft);
		if (pNode->pRight != nullptr)
			g_Queue.push(pNode->pRight);

		if (g_Queue.empty()) break;
		pNode = g_Queue.front();
		std::cout << pNode->iValue;
		g_Queue.pop();

		if (g_Queue.empty()) break;
		pNode = g_Queue.front();
	} while (pNode);
}
void QuadTree::CreaeBinaryNode(Node* pNode)
{
	if (pNode->iDepth == 2) return;
	pNode->pLeft = new Node(++g_iValue);
	//g_pArray[g_iValue] = pNode->pLeft;
	pNode->pRight = new Node(++g_iValue);
	//g_pArray[g_iValue] = pNode->pRight;
	pNode->pLeft->iDepth = pNode->iDepth + 1;
	pNode->pRight->iDepth = pNode->iDepth + 1;
	CreaeBinaryNode(pNode->pLeft);
	CreaeBinaryNode(pNode->pRight);
}