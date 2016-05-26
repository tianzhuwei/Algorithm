#include <iostream>
#include <time.h>
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
	//		change(ve[low],ve[middle]);
}

int  static Partition(int ve[],int low ,int high){
	int i=low;
	int j=high;
	int pivot=ve[low];

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
	return i;
}
void InsertSort(int *&ve,int low ,int high){
	int i,j,temp;
	for (j=low+1;j<=high;++j)
	{
		temp=ve[j];
		i=j-1;
		while(i>=0&&ve[i]>temp){
			ve[i+1]=ve[i];
			--i;
		}
		ve[i+1]=temp;
	}
}
void static qucik_sort_MiddleOfThree_Insert_Key(int ve[],int low,int high){
	if (low<high)
	{

		if (high-low+1<3)
		{
			InsertSort(ve,low,high);
			return;
		}
		MidanOfThree(ve,low,high);
		//int i=Partition(ve,low,high);

		//进行同key聚集;
		//进行左右分组,并且将与key相同元素放到两边;
		int first = low;
		int last  = high;
		int right =high;
		int left  = low;
		int leftlen= 0 ;
		int rightlen = 0 ;
		int key = ve[first];
		while( first <last){
			while( first<last && ve[last]>=key){
				if (ve[last] == key)
				{
					change(ve[last],ve[right]);
					right--;
					rightlen++;
				}
				last--;
			}
			ve[first] = ve[last];
			while (first<last && ve[first]<=key)
			{
				if (ve[first] == key)
				{
					change(ve[first],ve[left]);
					left++;
					leftlen++;
				}
				first++;
			}
			ve[last] = ve[first];
		}
		ve[first] = key;

		//将两边与KEY相等的元素放到key两边;

		int i = first-1;
		int j = low;
		while(j < left && ve[i] != key){
			change(ve[i],ve[j]);
			i--;
			j++;
		}
		i=last+1;
		j=high;
		while(j>right && ve[i]!=key){
			change(ve[i],ve[j]);
			j--;
			i++;
		}

		qucik_sort_MiddleOfThree_Insert_Key(ve,low,first-leftlen-1);
		qucik_sort_MiddleOfThree_Insert_Key(ve,first+rightlen+1,high);
		
	}

}
void putout(int ve[],int num){
	for (int i=0;i<num;++i)
	{
		cout<<ve[i]<<" ";
	}
	cout<<endl;
}
int main(){

	cout<<"以下运行结果是使用  三数取中+直接插入排序+同key相聚  快速排序思想进行优化！"<<endl;
	int * ve;
	int num=1000000;//一百万的数据;
	//int num=10;
	ve=new int[num];
	srand((unsigned)time(NULL));
	for (int i=0;i<num;++i)
		ve[i]=rand();
	clock_t time1=clock();
	qucik_sort_MiddleOfThree_Insert_Key(ve,0,num-1);
	time1=clock()-time1;
	cout<<"随机数组(一百万)耗时："<<time1<<"ms"<<endl;
	//		putout(ve,num);

	clock_t time2=clock();
	qucik_sort_MiddleOfThree_Insert_Key(ve,0,num-1);
	time2=clock()-time2;
	cout<<"升序数组(一百万)耗时："<<time2<<"ms"<<endl;
	//		putout(ve,num);
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
	}
	clock_t time3 =clock();
	qucik_sort_MiddleOfThree_Insert_Key(ve,0,num-1);
	time3=clock()-time3;
	cout<<"重复数组(一百万)耗时："<<time3<<"ms"<<endl;

	delete[] ve;
	ve=NULL;

	system("pause");
	return 0;
}