#include "FibonacciHeap.h"

FibonacciHeap_Head FibonacciHeap::Make_Heap() {//初始化一个空的 堆;
	FibonacciHeap_Head a;
	a.min = NULL;
	a.n = 0;
	return a;
}
void  FibonacciHeap::Insert(FibonacciHeap_Head *H, int x) {//将 x 结点插入 H ;
	H->n++;
	node* temp=H->min;
	node* x_temp = new node;
	x_temp->child = NULL;
	x_temp->parent = NULL;
	x_temp->pre = NULL;
	x_temp->next = NULL;
	x_temp->key = x;
	x_temp->mark = true;
	x_temp->degree = 0;

	if (temp==NULL)//如果H指向的为空;
	{
		H->min = x_temp;
		x_temp->pre = x_temp;
		x_temp->next = x_temp;
		return;
	}
	node* pre_temp = temp->pre;
	pre_temp->next = x_temp;
	x_temp->pre = pre_temp;
	x_temp->next = temp;
	temp->pre = x_temp;
}
node* FibonacciHeap::Minimum(FibonacciHeap_Head *H) {//返回指向最小结点的指针;

	return H->min;
}

FibonacciHeap_Head* FibonacciHeap::Union(FibonacciHeap_Head* H1, FibonacciHeap_Head* H2) {
	node* temp1 = H1->min;
	node* temp2 = H2->min;
	node* temp1_pre = temp1->pre;
	node* temp2_pre = temp2->pre;
	temp1_pre->next = temp2_pre;
	temp2_pre->next = temp1_pre;
	temp1->pre = temp2;
	temp2->pre = temp1;

	FibonacciHeap_Head* New_H = new FibonacciHeap_Head;
	New_H->n = H1->n + H2->n;
	if (H1->min->key >= H2->min->key)
	{
		New_H->min = H2->min;
	}
	else
	{
		New_H->min = H1->min;
	}
	return New_H;
}

void FibonacciHeap::Consolidate(FibonacciHeap_Head*H) {
	int d = log10(H->n)/(log10(1 + sqrt(5)));
	node* *A=new node*[d];
	for (int i = 0; i < d; ++i)
		A[i] = NULL;
}

node* FibonacciHeap::Extract_Min(FibonacciHeap_Head* H) {//删除最小关键字，并返回该指针;
	node* z = H->min;
	if (z!=NULL)
	{
		node* child ,*temp_child,* temp_pre;
		for (int i = 0; i < z->degree; i++)//将所有子孩子加入到根链表;
		{
			child = z->child;
			temp_child = child;
			z->child = child->next;

			temp_pre = z->pre;
			temp_pre->next = temp_child;
			temp_child->pre = temp_pre;
			temp_child->next = z;
			z->pre = temp_child;
		}//for;

		//将z移出根链表;
		if (z==z->next)
		{
			H->min = NULL;
		}
		else
		{
			//移除H->min指向的点;
			H->min->pre->next = H->min->next;
			H->min->next->pre = H->min->pre;

			H->min = H->min->next;
			Consolidate(H);
		}
			(H->n)--;
	}
	return z;

}


FibonacciHeap::FibonacciHeap()
{
}


FibonacciHeap::~FibonacciHeap()
{
}
