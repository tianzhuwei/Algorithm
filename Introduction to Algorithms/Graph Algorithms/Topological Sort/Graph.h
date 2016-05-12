#pragma once
#include <iostream>
#include<time.h>
#include <fstream>
#include <string>
#include <sstream>
#include <time.h>
using namespace std;
struct Edge 
{
	int vexName;//顶点名称;
	Edge* next;//指向的下一条边;
	int weight;//权重;
};
struct ArcNode
{
	int incount;//结点的入度;
	Edge* firstEdge;
	int visit;
};
class Graph
{
private:
	//;
	int edgeNum;//;
public:
	ArcNode* head;
	int vexNum;
private:
	void initGraph();
	void initArcNode();
	void dirGraph(int start,int end);
	void nodirGraph(int start,int end);
	void DFS(int v);
public:
	void Kahn();
	void Under_DFS();
	Graph(void);
	~Graph(void);
	void readfile();

};

