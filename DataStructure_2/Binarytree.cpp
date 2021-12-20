#include<iostream>
using namespace std;

struct Node
{
	int Depth;
	int value;
	Node* Left;
	Node* Right;
	Node(int i)
	{
		value = i;
		Left = nullptr;
		Right = nullptr;
	}
};
int g_val = 0;
Node* Binarynode(Node* node)
{
	if (node->Depth == 2) return nullptr;
	node->Left = new Node(++g_val);
	node->Right = new Node(++g_val);
	node->Left->Depth = node->Depth + 1;
	node->Right->Depth = node->Depth + 1;
	Binarynode(node->Left);
	Binarynode(node->Right);
}
void BinaryPrint(Node* node)
{
	if (node == nullptr)return;
	cout << node->value;
	BinaryPrint(node->Left);
	BinaryPrint(node->Right);
}
void main()
{
	Node* root = new Node(0);
	root->Depth = 0;
	Binarynode(root);
	BinaryPrint(root);
}