#include"general.h"
void PuSu_match(char* buffer,char* p);
int main() {
	clock_t time = clock();
	ifstream DNA("E:\\DNA.txt");
	//ifstream DNA("E:\\test.txt");
	if (!DNA)
	{
		cout << "Can not open the file!" << endl;
		system("pause");
		return 1;
	}
	DNA.seekg(0,DNA.end);
	unsigned length = DNA.tellg();
	DNA.seekg(0,DNA.beg);
	cout << "string length is "<<length << endl;
	char* buffer = new char[length+1];
	memset(buffer, 0, length+1);
	DNA.read(buffer, length+1);
	//cout << "the string is " << endl;
	//cout << buffer << endl;
	if (DNA.eof())
	{
		cout << "all chacter readed!" << endl;
	}
	else
	{
		cout << "error: only  " <<DNA.gcount() << "  could be read";
	}
	DNA.close();
	time = clock() - time;
	cout << "Read Use time is " << time << endl;
	
	char* p="TCTCCTTTTGGCTCTTTTTTGTTTTGTTTTCTGTCTTGCTCTTCAATGA";	
	//PuSu_match(buffer, p);
	delete[] buffer;
	system("pause");
  	return 0;
}