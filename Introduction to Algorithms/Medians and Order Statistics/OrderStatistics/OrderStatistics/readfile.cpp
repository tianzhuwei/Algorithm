#include<iostream>
#include<fstream>
#include<string>
using namespace std;
void readfile(int*arry){
	string filename= "E:\\raise.txt";
	ifstream readtxt(filename);
	if (!readtxt)
	{
		cout << "Can not open the file!" << endl;
		system("pause");
		exit(0);
	}

	//int num = 1000000;
	int i = 0;
	//int* arry = new int[num];
	int temp;
	while (!readtxt.eof())
	{
		readtxt >> temp;
		if (readtxt.fail())
		{
			break;
		}
		arry[i++]=temp;
	}
	cout << "Read Over!" << endl;
}
