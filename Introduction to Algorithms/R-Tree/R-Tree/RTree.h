#pragma once
#include<iostream>
#include<vector>
using namespace std;

struct Rectangle
{
	int leftPoint;
	int rightPoint;
};

struct Node;
struct childNode
{
	Rectangle region;
	Node* child;
	childNode() {
		child = NULL;
	}
};

struct Node
{
	Rectangle region;
	vector<childNode> child;
	Node* parent;
	Node() {
		parent = NULL;
	}
};

class RTree
{
public:
	int M;//M 阶R树;
	int m;//M 阶R树的内结点最少的元素个数，M/2 向上取整;
	Node * Root;//R树的根结点;
public:
	void Insert(Rectangle re);//向R树添加一个区域;
	
	RTree();
	~RTree();
private:
	Node* ChooseLeaf(Rectangle re);//返回要插入的叶子结点;
	void AdjustTree();//当插入一个新的元素后，可能造成结点不再符合R树性质，所以需要进行调整;

};

