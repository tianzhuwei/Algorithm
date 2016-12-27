#include"SuffixTree.h"
#include<time.h>
#include<fstream>
int main() {

	//fstream readfile("E:\\test.txt");
	fstream readfile("250.txt");
	while (!readfile)
	{
		cout << "Can not open the file !" << endl;
		system("pause");
		exit(0);
	}
	string s;// = "ABCABXABCD";
	getline(readfile, s);
	readfile.close();
	cout << "Read Over ! " << endl;
	SuffixTree test;
	clock_t time = clock();
	test.bulid(s);
	
	cout << "use time " << clock() - time << " ms" << endl;
	system("pause");
	return 0;
}