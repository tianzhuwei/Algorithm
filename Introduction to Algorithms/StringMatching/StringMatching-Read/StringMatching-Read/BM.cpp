#include	"general.h"

/*
i注意：
当我写下这个 代码的时候我毕不理解！！！！！！！！！！
脑子已经进水
*/

void PreBmBc(char*p,int* bmbc ) {
	int p_length = strlen(p);
	for (int i = 0; i < p_length; i++)
	{
		bmbc[i] = p_length;
	}
	for (int i  = 0; i < p_length; i++)
	{
		bmbc[p[i]] = p_length - i - 1;
	}
}
void Suffixes(char* p, int* suff) {
	int p_length = strlen(p);
	int q;
	suff[p_length - 1] = p_length;
	for (int i = p_length - 2; i >= 0; --i) {
		q = i;
		while (q>=0&& p[q]==p[p_length-1-i+q])
		{
			--q;
		}//while
		suff[i] = i - q;
	}
}
void preBmGs(char* p, int* suff,int * bmGs) {
	int p_length = strlen(p);
	for (int i = 0; i < p_length; i++)
	{
		bmGs[i] = p_length;
	}
	int j = 0;
	for (int i = p_length-1; i >=0; --i)
	{
		if (suff[i]==i+1)
		{
			for ( ;  j<p_length -1-i ;++j)
			{
				if (bmGs[j]==p_length)
				{
					bmGs[j] = p_length - 1 - i;
				}
			}
		}
	}//for;
	for (int i = 0; i < p_length-2; i++)
	{
		bmGs[p_length - 1 - suff[i]] = p_length - 1 - i;
	}
}
void BM(char* buffer, char* p) {
	int count = 0;
	int* bmbc = new int[128];//用来表示p中的某个字符所在位置的下标;
	memset(bmbc, -1, 128 * sizeof(int));//全部初始化为-1;
	PreBmBc(p, bmbc);
	int p_length = strlen(p);
	int b_length = strlen(buffer);
	int i = 0, j = p_length-1;//i用来表示文本buffer当前的指示，j用来指示模式p当前的指示；
	int temp = 0;
	int* suff = new int[p_length];   //suff[i]=s  表示截取到i位置，有s个字符匹配 ; 
	memset(suff, 0, p_length * sizeof(int));
	Suffixes(p, suff);
	int* bmGs = new int[p_length];//bmGs[i] 表示遇到好后缀时，模式串应该移动的距离，其中i表示好后缀前面一个字符的位置（也就是坏字符的位置）;
	preBmGs(p, suff, bmGs);
	while (i<=b_length-p_length)
	{
		for (j=p_length-1; j >= 0 && buffer[i + j] == p[j]; --j);
		if (j<0)
		{
//			cout << "shift " << i << endl;
			//i +=bmGs[0];
			i += p_length;
			count++;
		}
		else
		{
			i += bmGs[j];
			temp = bmbc[buffer[i + j]] - (p_length - 1) + j;
			if (i<temp)
			{
				i += temp;
			}
		}
	}
	cout << "Number is " << count << endl;
/*
	while (i<b_length-p_length)
	{
		temp = i + p_length-1;
		while (p[j]==buffer[temp]&&j>=0&&temp>=0)
		{
			temp--;
			j--;
		}
		if (j==0)
		{
			cout << "shift " << temp << endl;
			j = p_length;
			i += p_length;
		}
		else
		{
			if (bmbc[buffer[temp]]!=-1)//利用坏字符规则来计算  i  应该在的位置;   开始
			{
				i = temp - bmbc[buffer[temp]];
				j = p_length - 1;
			}//利用坏字符规则来计算  i  应该在的位置;   结束
			else
			{
				i = temp + 1;
				j = p_length - 1;
			}
			//下面我们利用好后缀的规则来计算得出  i  应该在的位置     开始;
			//标记数组已经写出来  bmGs[ ]
			if (bmGs[temp]>i)
			{
				i = bmGs[i];
			}
			//好后缀规则    结束;
		}//else
	}
	*/
}