#include"Graph.h"
int main() {
	Graph test;
	clock_t time = clock();
	test.BellmanFord();
	//test.Dijkstra();
	time = clock() - time;
	cout << "The end ! Use time " << time << " ms" << endl;
	system("pause");
	return 0;
}