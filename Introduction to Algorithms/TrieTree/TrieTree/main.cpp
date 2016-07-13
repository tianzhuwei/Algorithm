#include"Trie.h"
#include<fstream>
#include<string>
int main() {
	Trie test;
	node* TT = test.MakeTrie();
	ifstream readfile("E:\\dict.txt");
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
	test.search(TT, "zygosphere");
	test.search(TT, "a");
	test.Delete(TT, "zygosphere");
	test.search(TT, "zygosphere");

	system("pause");
 	return 0;
}