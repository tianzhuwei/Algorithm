#pragma once
#include<iostream>
using namespace std;
enum color { Red = 0,Black=1 };
struct Node
{
	color color;//0代表红    1 代表黑;
	Node* parent;
	Node* leftChild;
	Node* rightChild;
	int key;
	Node() {
		parent = NULL;
		leftChild = NULL;
		rightChild = NULL;
		color = Red;
	}
};
class RedBlackTree
{
private:
	void RBInsertFixup(Node* node);
	void RightRotate(Node* node);
	void LeftRotate(Node* node);
	void RBTransplant(Node* u,Node* v);
	Node* TreeMinmum(Node* node);
	void RBDeleteFixup(Node* node);
public:
	Node* root;
	Node* nil;
public:
	RedBlackTree();
	~RedBlackTree();
	void RBInsert(Node* node);
	void RBDelete(Node* node);
	Node* RBSearch(int key);
};

