#include"Trie.h"
#include<fstream>
#include<string>
#include<time.h>
int main() {
	Trie test;
	clock_t time = clock();
	node* TT = test.MakeTrie();
	ifstream readfile("E:\\dict.txt");
	//ifstream readfile("E:\\female.txt");
	if (!readfile)
	{
		cout << "Can not open the file !¡¡" << endl;
		system("pause");
		exit(0);
	}
	string words;

	while (!readfile.eof())
	{
		readfile >> words;
		if (readfile.fail())
		{
			break;
		}
		const char*a= words.c_str() ;
		test.Insert(TT, a);
	}
	cout << "Completed! use time " << clock()-time << " ms" << endl;
	readfile.close();
//	time = clock();
//	ifstream readfile1("E:\\dict.txt");
	//ifstream readfile1("E:\\female.txt");
	//if (!readfile1)
	//{
	//	cout << "Can not open the file !¡¡" << endl;
	//	system("pause");
	//	exit(0);
	//}
	//while (!readfile1.eof())
	//{
	//	readfile1 >> words;
	//	if (readfile1.fail())
	//	{
	//		break;
	//	}
	//	const char*a = words.c_str();
	//	//test.search(TT, a);
	//	test.Delete(TT, a);
	//}
	//time = clock() - time;
	//cout <<"use time: "<< time<<"ms" << endl;

	system("pause");
 	return 0;
}