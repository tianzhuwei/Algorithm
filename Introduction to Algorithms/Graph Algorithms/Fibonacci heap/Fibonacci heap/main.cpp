#include"FibonacciHeap.h"

int main() {
	FibonacciHeap test;
	FibonacciHeap_Head* head =test.Make_Heap();

	for (int i = 0; i < 10; i++)
	{
		node* t = new node;
		t->child = NULL;
		t->degree = 0;
		t->key = rand();
		t->next = NULL;
		t->pre = NULL;
		t->parent = NULL;
		test.Insert(head,t );
	}
	cout << test.Minimum(head) << endl;;

	system("pause");
	return 0;
}