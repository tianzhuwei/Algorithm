#pragma once
#include<iostream>
#include<time.h>
#include<fstream>
using namespace std;
struct Edge
{
	int VexName;//顶点名称;
	Edge* next;
};

struct ArcNode
{
	Edge* firstEdge;
	int inCount;//用来表示顶点的入度;
};

class Graph
{
public:
	ArcNode* head;

public:
	void Kosaraju();
	void Tarjan();
	void Gabow();
	Graph(int num);
	Graph();
	~Graph();

private:
	int vexNum;
	int EdgeNum;

	//Kosaraju
	ArcNode* Reverse_head;
	int* stack;//按访时间由小到大进栈;
	int stack_top; 
	ArcNode* NodeLink();//反向图结点链表;
	int* K_mark;//用来标记强连通分量，同一个连通分量有同一个值;
	int K_id;
	bool* K_visit;//标记顶点是否被访问过;

	//Tarjan
	int* DFN;//存储当前顶点访问的时间（顺序）;
	int* LOW;//存储当前顶点指向根结点的访问时间（顺序）;
	bool* ifInStack;
	int T_id;
	int* T_mark;
	bool* T_visit;
	int T_pre;//访问顺序；

	//Gabow;
	int* Path;
	int* Root;
	int Path_Top;
	int Root_Top;
	int* G_pre;//访问的先后顺序;
	int G_time;//记录时间;
	bool* G_visit;
	int  G_id;
	int* G_mark;

private:
	void initGraph(int num);
	void addDirEdge(ArcNode* head1,int start, int end);
	void Kosaraju_Reverse();//对原图进行取反操作;
	void Kosaraju_DFS(int num);
	void DFS(int begin);
	void Tarjan_DFS(int num);
	int min(int a, int b);
	void Gabow_DFS(int num);
};

