#include"general.h"
void PuSu_match(char* buffer, char* p) {
	clock_t time = clock();
	int count = 0;
	cout << "PuSu_match begin ! " << endl;
	int p_length = strlen(p);
	int buffer_length=strlen(buffer) ;
	int a = buffer_length - p_length;
	for (int i = 0; i <=a; i++)
	{
		int j = 0;
		while ( j<p_length )
		{
			if (buffer[i+j]==p[j])
			{
				++j;
			}
			else
			{
				break;
			}
		}
		if (j<p_length)
		{
			continue;
		}
		else
		{
			count++;
			//cout << i << endl;
		}
	}//for
	time = clock() - time;
	cout << "PuSu_match :total " << count << endl;
	cout << "PuSu_match end ! use time "<<time <<"ms"<< endl;
};