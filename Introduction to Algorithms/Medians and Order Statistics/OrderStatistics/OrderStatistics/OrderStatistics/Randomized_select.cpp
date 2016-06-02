#include<iostream>
#include<time.h>
using namespace std;
void change1(int &a, int &b) {
	int t = a;
	a = b;
	b = t;
}
void random(int low, int high, int *arry) {
	if (low<high)
	{
		srand((unsigned)time(NULL));
		int r = rand() % (high - low);
		r = r + low + 1;
		change1(arry[r], arry[high]);
	}
}
int partition(int low, int high, int *arry) {
		random(low, high, arry);
		int temp = arry[high];
		int i = low - 1, j = low;
		for (; j <high ; j++)
		{
			if (arry[j]<=temp)
			{
				++i;
				change1(arry[i], arry[j]);
			}
		}
		change1(arry[++i], arry[high]);
		return i;
}
void Randomized_select(int low ,int high,int *arry,int pos){
	int pivot = partition(low, high, arry);
	if (pivot==pos)
	{
		cout << "In the " << pos+1 << "number is " << arry[pos] << endl;
	}
	else if (pivot>pos)
	{
		Randomized_select(low, pivot - 1, arry, pos);
	}else
		Randomized_select(pivot + 1,high, arry, pos);
}
