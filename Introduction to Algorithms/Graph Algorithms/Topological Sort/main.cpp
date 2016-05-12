#include "Graph.h"
int main(){

	Graph test;
//	test.readfile();
	test.Kahn();
	for(int i=0;i<test.vexNum;++i){
		test.head[i].visit=0;
	}
	test.Under_DFS();
	system("pause");
	return 0;
}