#include <iostream>
#include <time.h>
using namespace std;

void qucik_sort_origin(int ve[],int low,int high){
	if (low<high)
	{
		int i=low;
		int j=high;
		int pivot=ve[i];

		while (i!=j)
		{
			while(ve[j]>=pivot&&i<j) 
				j--;
			if (i<j)
			{
				ve[i]=ve[j];
				i++;
			}
			while(ve[i]<=pivot&&i<j)
				i++;
			if(i<j){
				ve[j]=ve[i];
				j--;
			}
		}
		ve[i]=pivot;
		qucik_sort_origin(ve,low,i-1);
		qucik_sort_origin(ve,i+1,high);
	
	}

}
int main(){

	cout<<"以下运行结果是使用  原始  快速排序思想没有进行优化！"<<endl;
	int * ve;
	int num=1000000;//一百万的数据;
	ve=new int[num];
	srand((unsigned)time(NULL));
	for (int i=0;i<num;++i)
		ve[i]=rand();
	clock_t time1=clock();
	qucik_sort_origin(ve,0,num-1);
	time1=clock()-time1;

	cout<<"随机数组(一百万)耗时："<<time1<<"ms"<<endl;
	clock_t time2=clock();
	qucik_sort_origin(ve,0,num-1);
	time2=clock()-time2;
	cout<<"升序数组(一百万)耗时："<<time2<<"ms"<<endl;

	for (int i=0;i<num;++i)
	{
		if (i%7==0)
		{
			ve[i]=5;
		}else if (i%7==1)
		{
			ve[i]=7;
		}else if (i%7==2)
		{
			ve[i]=6;
		}else if (i%7==3)
		{
			ve[i]=8;
		}else if (i%7==4)
		{
			ve[i]=4;
		}else if (i%7==5)
		{
			ve[i]=6;
		}else if (i%7==6)
		{
			ve[i]=1;
		}
		//	cout<<ve[i]<<"  ";
	}
	clock_t time3 =clock();
	qucik_sort_origin(ve,0,num-1);
	time3=clock()-time3;
	cout<<"重复数组(一百万)耗时："<<time3<<"ms"<<endl;


	delete[] ve;
	ve=NULL;

	system("pause");
	return 0;
}