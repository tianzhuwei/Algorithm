#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <stdio.h>
using namespace std;
typedef struct Edge{
	int vName;
	int weight;
	Edge* nextEdge;
}Edge;

typedef struct ArcNode{
//	int adjvex;
	Edge * next;
	bool statu;
}ArcNode;//顶点，链表头;

class Graph
{
public:
	Graph(void);
	~Graph(void);
	void creat_Linklist_Nodirection();//创建一个无向图;
	void creat_Linklist_Direction();//创建一个有向图;
	void BFS();
	void BFS_self();
	void DFS();
	void DFS_digui();
	void DFS_self();
public:
	ArcNode* head;
//private:
	int vex_num;//顶点个数;
	int edge_num;//边的个数;
private:
	//测试缓冲区;
	void read();
	void inputvexnum();
	void inputedgenum();
	void createVertexArry();
	void addedgeinfo_nodirection();
	void addedgeinfo_direction();
	void addedge_nodirection(int start,int end,int weight);
	void addedge_direction(int start,int end,int weight);
	void DFS_Sin(int v);
};

