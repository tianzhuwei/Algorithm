#include"RedBlackTree.h"
#include<fstream>
#include<time.h>
int main() {
	clock_t time = clock();
	RedBlackTree test;
	string filename = "E:\\B+\\large.txt";
	fstream readfile(filename);
	if (!readfile)
	{
		cout << "Can not open the file! " << endl;
		system("pause");
		return 0;
	}
	int te;
	Node* a;
	while (!readfile.eof())
	{
		readfile >> te;
		a = new Node;
		a->key = te;
		a->color = Red;
		//a->leftChild = test.nil;
		//a->rightChild = test.nil;
		//a->parent = test.nil;
		if (readfile.fail())
		{
			break;
		}
		test.RBInsert(a);
	}
	readfile.close();
	cout << "Insert complete ,use time " << clock() - time << "ms" << endl;
	time = clock();
	//next test delete ;
	fstream readfile1(filename);
	if (!readfile1)
	{
		cout << "Can not open the file! " << endl;
		system("pause");
		return 0;
	}
	while (!readfile1.eof())
	{
		readfile1 >> te;
		if (readfile1.fail())
		{
			break;
		}
//		cout << te << " ";
		a = test.RBSearch(te);
		test.RBDelete(a);
	}
	readfile1.close();
	cout << "Delete complete, use time " << clock() - time << "ms" << endl;
	
	system("pause");
	return 0;
}