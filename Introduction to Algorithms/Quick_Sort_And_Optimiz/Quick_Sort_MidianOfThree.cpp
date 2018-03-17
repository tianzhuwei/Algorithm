#include <iostream>
#include <time.h>
#include <algorithm>
#include <vector>
using namespace std;

void change(int &a,int& b){
	if(a!=b){a^=b;b^=a;a^=b;}
}

void MidanOfThree(int*& ve, int low ,int high){
 	int middle=(low+high)/2;
	if (ve[middle]>ve[high])
	{
		change(ve[middle],ve[high]);
	}
	if (ve[low]>ve[high])
	{
		change(ve[low],ve[high]);
	}
	if (ve[low]<ve[middle])
	{
		change(ve[low],ve[middle]);
	}
	//change(ve[low],ve[middle]);
}

int  Partition(int ve[],int low ,int high){
	int i=low;
	int j=high;
	int pivot=ve[low];

	while (i!=j)
	{
		while(ve[j]>pivot&&i<j) 
			j--;
		if (i<j)
		{
			ve[i]=ve[j];
			i++;
		}
		while(ve[i]<pivot&&i<j)
			i++;
		if(i<j){
			ve[j]=ve[i];
			j--;
		}
	}
	ve[i]=pivot;
	return i;
}

void qucik_sort_MiddleOfThree(int ve[],int low,int high){
	if (low>=high)
	{
		return;
	}
	MidanOfThree(ve,low,high);
	int i=Partition(ve,low,high);
	qucik_sort_MiddleOfThree(ve,low,i-1);
	qucik_sort_MiddleOfThree(ve,i+1,high);
}
void putout(int ve[],int num){
	for (int i=0;i<num;++i)
	{
		cout<<ve[i]<<" ";
	}
	cout<<endl;
}
int main(){

	cout<<"以下运行结果是使用  三数取中  快速排序思想没有进行优化！"<<endl;
	int * ve;
	int num=1000000;//一百万的数据;
	//int num=10000;
	ve=new int[num];
	srand((unsigned)time(NULL));
	for (int i=0;i<num;++i)
		ve[i]=rand();
	clock_t time1=clock();
	qucik_sort_MiddleOfThree(ve,0,num-1);
	time1=clock()-time1;
	cout<<"随机数组(一百万)耗时："<<time1<<"ms"<<endl;
//	putout(ve,num);

	clock_t time2=clock();
	qucik_sort_MiddleOfThree(ve,0,num-1);
	time2=clock()-time2;
	cout<<"升序数组(一百万)耗时："<<time2<<"ms"<<endl;
//	putout(ve,num);
	for (int i=0;i<num;++i)
	{
		ve[i]=10;
	}
	clock_t time3 =clock();
	qucik_sort_MiddleOfThree(ve,0,num-1);
	time3=clock()-time3;
	cout<<"重复数组(一百万)耗时："<<time3<<"ms"<<endl;


	delete[] ve;
	ve=NULL;

	system("pause");
	return 0;
}
