#pragma once
#include<iostream>
#include<cmath>

using namespace std;

struct node
{
	bool mark;//标记域，现在不知道干什么;
	node* parent;//指向父结点;
	node* child;//指向孩子结点;
	node* pre;//结点的前指针;
	node* next;//结点后指针；
	int key;//关键字的值;
	int degree;
};
struct FibonacciHeap_Head
{
	node* min;//指向最小的点;
	int n;//堆中顶点的个数;
};
class FibonacciHeap
{
public:
	//FibonacciHeap_Head H;//FibonacciHeap 可以有，也可以没有，先注释
	
public:
	FibonacciHeap_Head* Make_Heap();//初始化一个空的 堆;
	void Insert(FibonacciHeap_Head *H,node* x);//将 x 结点插入 H ;
	node* Minimum(FibonacciHeap_Head *H);//返回指向最小结点的指针;
	node* Extract_Min(FibonacciHeap_Head* H);//删除最小关键字，并返回该指针;
	FibonacciHeap_Head* Union(FibonacciHeap_Head* H1, FibonacciHeap_Head* H2);
	FibonacciHeap();
	~FibonacciHeap();

private:
	void Consolidate(FibonacciHeap_Head* H);
	void swap(node* a,node* b);
	void Heap_Link(node* small,node* big);
private:

};

