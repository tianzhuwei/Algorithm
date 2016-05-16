#include "Graph.h"

int main(){
	int num=-1;
	cout<< "Please choose the number you want to test:" << endl; 
	cout << "0-test.txt" << endl;
	cout << "1-xmark.txt" << endl;
	cout << "2-uniprot22m.txt" << endl;
	cout << "3-uniprot100m.txt" << endl;
	cout << "4-uniprot150m.txt" << endl;
	while (num>4||num<0)
	{
		cout << "input the number:" << endl;
		cin >> num;
	}
	Graph test(num);

	//test.Kosaraju();

	//test.Tarjan();

	test.Gabow();
	system("pause");
	return 0;
}