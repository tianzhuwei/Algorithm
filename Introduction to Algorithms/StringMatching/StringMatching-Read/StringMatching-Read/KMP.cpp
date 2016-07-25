#include"general.h"
int* Compute_Prefix_Function(char* p) {
	int p_length = strlen(p);
	int* next = new int[p_length+1];
	int j = 1;//
	int k = 0;//表示已经匹配的个数;
	next[0] = 0;
	while (j <= p_length) {
		while (k > 0 && p[k] != p[j])
			k = next[k - 1];
		if (p[k]==p[j])
			k++;
		next[j++] = k;
	}

	return next;
}
void KMP(char* buffer, char* p) {
	int count = 0;
	int buffer_length = strlen(buffer);
	int p_length = strlen(p);
	int* next = Compute_Prefix_Function(p);//next[i]中存储的值表示有 （i+1）个字符的时候最大公共前后缀是多少;
	int q = 0;//q用来表示已经匹配的个数;
	for (int i = 0; i < buffer_length; i++)//i用来表示原字符串里面当前匹配的个数;
	{
		while (q>0 && p[q]!=buffer[i])
			q = next[q-1];//下标为(q-1)时已经匹配的个数为q;

		if (p[q]==buffer[i])
			q++;

		if (q==p_length)
		{
//			cout << "Pattern occurs with shift " << i - p_length+1 << endl;
			q = next[q-1];
			count++;
		}
	}//for
	cout << "Kmp : number is " << count << endl;
}