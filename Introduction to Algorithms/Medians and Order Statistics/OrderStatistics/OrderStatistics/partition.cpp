#include<iostream>
using namespace std;
void random(int low, int high, int *arry);
int partition(int low, int high, int *arry){
	if (low<high)
	{
		random(low, high,arry);
		int temp = arry[low];
		int i = low, j = high;
		while (i<j)
		{
			while (arry[j] > temp && i < j)
				j--;
			if (i < j){
				arry[i] = arry[j];
				i++;
			}
			while (arry[i] < temp && i < j)
				i++;
			if (i < j)
			{
				arry[j] = arry[i];
				j--;
			}
		}//while
		arry[i] = temp;
		return i;
	}//if

}