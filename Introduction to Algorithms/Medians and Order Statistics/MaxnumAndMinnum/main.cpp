#include<iostream>
#include<fstream>
#include<time.h>
#include<string>
#define num  1000000

using namespace std;
void MinAndMax(int *a){
	int min, max;
	int bigger, smaller;
	int i = 2;
	if (a[0]>a[1])
	{
		max = a[0];
		min = a[1];
	}
	else
	{
		max = a[1];
		min = a[0];
	}
	while (i!=num-1)
	{
		if (a[i]>a[i+1])
		{
			bigger = a[i];
			smaller = a[i + 1];
			i++;
		}
		else
		{
			bigger = a[i + 1];
			smaller = a[i];
			i++;
		}
		if (bigger>max)
		{
			max = bigger;
		}
		if (smaller<min)
		{
			min = smaller;
		}
	}
	cout << "Max=" << max << "  " << "Min=" << min << endl;
}
int main(){
	clock_t time = clock();
	string filename = "E:\\test.txt";
	ifstream txt(filename);
	if (!txt)
	{
		cout << "Can not lopen the file!" << endl;
		exit(0);
	}
	cout << "Open the " << filename << endl;

	int* arry;
	arry = new int[num];
	memset(arry, 0, num*sizeof(int));
	int i = 0;
	int temp;
	while (!txt.eof())
	{
		txt >> temp;
		if (txt.fail())
		{
			break;
		}
		arry[i++] = temp;
	}
	MinAndMax(arry);
	time = clock() - time;
	cout << "The programa use time " << time << endl;
	system("pause");
	return 0;

}