#include"FibonacciHeap.h"
#include<fstream>
#include<time.h>
int main() {
	FibonacciHeap test;
	clock_t time = clock();
	FibonacciHeap_Head* head =test.Make_Heap();
	fstream readfile("E:\\repeat.txt");
	node* t = new node;
	while (!readfile.eof())
	{
		readfile>>t->key;
		test.Insert(head, t);
	}
	//cout << "Init time " << clock() - time <<"MS"<<endl;
	//
	//time = clock();
	//while (head!=NULL)
	//{
	//	test.Extract_Min(head);
	//}
	test.Minimum(head);
	cout << "Use time " << clock() - time << "MS" << endl;
	system("pause");
	return 0;
}