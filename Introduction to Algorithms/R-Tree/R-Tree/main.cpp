#include"RTree.h"
#include<fstream>
#include<time.h>
int main()
{
	clock_t time = clock();
	RTree test;
	Rectangle re;
	int number=0;//用来检查插入的数据个数；
	ifstream readfile("E:\\RTreeData\\CArdline.fnl");
	//ifstream readfile("E:\\RTreeData\\NArdline.fnl");
	//ifstream readfile("E:\\RTreeData\\CDrdline.fnl");
	if (!readfile)
	{
		cout << "Can not open the file !" << endl;
		system("pause");
		exit(0);
	}
	//
	int temp;
	while (!readfile.eof())
	{
		readfile >>re.leftPoint_x>>re.rightPoint_y>>re.rightPoint_x>>re.leftPoint_y >>temp>>temp;
		if (readfile.fail())
		{
			break;
		}
		test.Insert(re);
		number++;
	}
	cout << "insert "<<number <<" data"<< endl;
	cout << "use time " << clock() - time << " ms" << endl;
	system("pause");
	return 0;
}