#include"Graph.h"
#include<array>
#include<time.h>
int main() {
	Graph test;
	clock_t  time = clock();

	test.Relabel_To_Front();

	cout << "use time " << clock() - time << " MS" << endl;
	system("pause");
	return 0;
}