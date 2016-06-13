#include	"general.h"
void PreBmBc(char*p,int* bmbc ) {

}
void Suffixes(char* p, int* suff) {
	int p_length = strlen(p);
	suff[p_length - 1] = p_length;

	for (int i = p_length - 2; i > 0; ++i) {

	}
}
void BM(char* buffer, char* p) {
	int* bmbc = new int[128];
	memset(bmbc, -1, 128 * sizeof(int));
	PreBmBc(p, bmbc);
	int p_length = strlen(p);
	int b_length = strlen(buffer);
	int i = 0, j = p_length-1;//i用来表示文本buffer当前的指示，j用来指示模式p当前的指示；
	int temp = 0;
	int* suff = new int[p_length];   //suff[i]=s  表示截取到i位置，有s个字符匹配 ; 
	memset(suff, 0, p_length * sizeof(int));
	Suffixes(p, suff);
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
			}
			else
			{
				j = p_length - 1;
				i = temp+1;
			}//利用坏字符规则来计算  i  应该在的位置;   结束

			//下面我们利用好后缀的规则来计算得出  i  应该在的位置     开始;



			//好后缀规则    结束;


		}//else
	}
}