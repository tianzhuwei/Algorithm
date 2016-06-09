#include"general.h"
int* Compute_Prefix_Function(char*p) {
	int p_length = strlen(p);
	int * next = new int[p_length + 1];
	next[0] = 0;
	next[1] = 0;
	int k = 0;//暂时理解为已经匹配的个数;
	for (int q = 2; q <= p_length; q++)//注意起始的长度，当下标从1开始记录的时候;
	{
		while (k>0 && p[k + 1] != p[q])
		{
			k = next[k];
		}
		if (p[k + 1] == p[q])
		{
			k++;
		}
		next[q] = k;
	}//for;

	return next;
}
void KMP(char* buffer, char* p) {
	int buffer_length = strlen(buffer);
	int p_length = strlen(p);
	int* next = Compute_Prefix_Function(p);
	int q = 0;
	for (int i = 0; i < buffer_length; i++)
	{
		while (q>0 && p[q+1]!=buffer[i])
		{
			q = next[q];
		}//while
		if (p[q+1]==buffer[i])
		{
			q++;
		}
		if (q==p_length)
		{
			cout << "Pattern occurs with shift " << i - p_length << endl;
			q = next[q];
		}
	}//for
}

