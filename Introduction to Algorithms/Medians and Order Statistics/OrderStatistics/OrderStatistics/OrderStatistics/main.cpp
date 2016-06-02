#include<iostream>
#include<time.h>
#include<fstream>
#define num 1000000
using namespace std;
void readfile(int* arry);
void Randomized_select(int low, int high, int *arry, int pos);
int Select(int* arry,int left,int right,int pos);
int main(){
	int* arry;
	arry = new int[num];
	readfile(arry);
	int pos=1;
	int aa = 0;
	while (pos)
	{
		cout << "Please input the pos(from 1 to  " << num << ")" << endl;
		cin >> pos;
		aa = pos;
		if (aa>0&&aa<num)
		{
			aa--;
			clock_t time = clock();
			Randomized_select(0, num - 1, arry, aa);
			//int a=Select(arry,0,num-1,pos);
			time = clock() - time;
			cout << "use time " << time << endl;
		}
		else
		{
			cout << "input erro!!" << endl;
		}

	}

	system("pause");
	return 0;
}
