#include<iostream>
#include<time.h>
using namespace std;
void random(int low, int high, int *arry){
	srand((unsigned)time(NULL));
	int r = rand() % (high - low) + low + 1;
	//Ωªªªarry[r]”Îarry[low]
	if (arry[r]!=arry[low])
	{
		arry[r] ^= arry[low];
		arry[low] ^= arry[r];
		arry[r] ^= arry[low];
	}
}/*
void change(int &a, int& b){
	if (a != b){ a ^= b; b ^= a; a ^= b; }
}*/