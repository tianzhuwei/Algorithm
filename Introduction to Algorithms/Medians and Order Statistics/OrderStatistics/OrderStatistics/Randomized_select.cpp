#include<iostream>
using namespace std;
int partition(int low, int high, int *arry);
void Randomized_select(int low ,int high,int *arry,int pos){
	int pivot = partition(low, high, arry);
	if (pivot==pos)
	{
		cout << "In the " << pos << "number is " << arry[pos] << endl;
	}
	else if (pivot>pos)
	{
		Randomized_select(low, pivot - 1, arry, pos);
	}else
		Randomized_select(pivot + 1,high, arry, pos);
}
