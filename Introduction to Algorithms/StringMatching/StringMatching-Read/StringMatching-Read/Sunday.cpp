#include"general.h"
void IsInP(char* p, int * arr) {
	int p_length = strlen(p);
	int i = p_length-1;
	while (i>=0)
	{
		if (arr[p[i]]==-1)
		{
			arr[p[i]] = i;
		}
		--i;
	}
}
void Sunday(char* buffer, char* p) {
	int i = 0, j = 0;//i用来指示buffer文本当前操作的字符位置，j用来指示模式当前操作的字符位置;
	int temp = 0;
	int b_length = strlen(buffer);
	int p_length = strlen(p);
	int* arry1=new int[128];
	memset(arry1, -1, sizeof(int) * 128);
	IsInP (p,  arry1);//arry1用来存放某个字符在模式p中最右端的位置;
	while (i<b_length)
	{
		if (buffer[i]==p[j])
		{
			if (j==p_length-1)
			{
				cout << "shift " << i+1-p_length << endl;
				j = 0;
				i++;
				continue;
			}
			i++;
			j++;
		}//if;
		else
		{
			temp = i + p_length - j;
			//如果buffer[temp]出现在模式p中，则与最端的对齐
			if (temp>strlen(buffer))
			{
				break;
			}
			if (arry1[buffer[temp]]!=-1)
			{
				j = 0;
				i = temp - arry1[buffer[temp]];
			}
			else
			{
				j = 0;
				i = temp + 1;
			}
		}
	}
}