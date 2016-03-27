#include <iostream>
using namespace std;
//这个程序是用来判断一个序列是否是一个二叉树的后序遍历;
/*主要思想： 设一个二叉查找树的后序遍历顺序是   D E B F G C A ;
	则我们可以知道A为这棵树的 根结点  从后到前进行比较当遇到比A小的时候 之后的点即为A的左子树，进行递归调用即可;
*/
int check(int a[],int start,int end){
	if (start<=end){

		int i=end-1;
		for (;a[i]>a[end]&&i>=0;--i)
		{
		}
		
		//i即为这个序列的区分点，将整个序列分为两个序列其中（start,i）为小于根的部分，（i+1,end）为大于根的部分;
		for (int j=i;j>=0;j--)
		{
			if (a[j]>a[end])
			{
				cout<<"no"<<endl;
				return 0;//返回0代表不是;
			}
		}
		check(a,start,i);
		check(a,i+1,end-1);
	}
	return 1;
}

int  main(){

	int a[1]={5};
	int result=check(a,0,0);
	if (result==1)
	{
		cout<<"yes"<<endl;
	}

	system("pause");
	return 0;
}
