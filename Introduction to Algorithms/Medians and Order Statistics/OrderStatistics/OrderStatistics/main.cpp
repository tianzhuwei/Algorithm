#include<iostream>
#include<time.h>
#include<fstream>
#define num 1000000
using namespace std;
void readfile(int* arry);
void Randomized_select(int low, int high, int *arry, int pos);
void Select(int* arry,int pos);
int main(){
	int* arry;
	arry = new int[num];
	readfile(arry);
	int pos;
	cout << "Please input the pos(from 0 to  "<<num-1<<")" << endl;
	cin >> pos;
	clock_t time = clock();

	//Randomized_select(0, num-1, arry, pos);
	Select(arry,pos);

	time = clock() - time;
	cout << "use time " << time << endl;
	system("pause");
	return 0;

}