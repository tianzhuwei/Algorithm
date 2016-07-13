#pragma once
#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;

struct Node
{
	vector<int>*key;//用于存放关键字的数组;
	vector<Node*>*child;//用于存放孩子指针的数组;
	Node* parent;//存储父亲结点;
	Node* next;//用于叶子结点指向下一下叶子结点;
	Node* pre;//用于叶子结点指向上一下叶子结点;
	Node() {
		next = NULL;
		pre = NULL;
		parent = NULL;
		key = new vector<int>;
		child = new vector<Node*>;
	}
};

class bPlus
{
public:
	Node* head;
public:
	bPlus();
	~bPlus();
	void addKey(int key);
	void deletekey(int key);
	Node* search(int key);
private:
	int m;//B+ 树的阶数，私每个结点关键字的个数是 (m/2)~m   ;  根结点至少有两个关键字  ;            ！！！！！！！！！！！目前只能选偶数
	int min;//结点最小个数;
private:
	void InitBplus();
	void InsertSort(vector<int>* ve);
	void Union(Node* node);
	void changeBig(Node* node,int key);
	void changeSmall(Node* node);
	void BrrowKey(Node* deleteNode, Node* brother);
	void leavesUnion(Node* left,Node* right);
};