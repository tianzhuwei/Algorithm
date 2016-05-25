#pragma once
#include<iostream>
#include<time.h>
#include<fstream>
#include<string>
#include<vector>
#include<functional>
#include<queue>
#include<algorithm>
#include"QuickSort.h"
using namespace std;

struct Edge
{
	int id;
	int start;
	int end;
	double weight;
	Edge* next;
	friend bool operator< (Edge a, Edge b)
	{
		return a.weight > b.weight;
	}
};
struct ArcNode
{

	Edge* firstEdge;
};

struct Union_head;

struct Union_struct
{
	int vexnum;
	Union_head* head;
	Union_struct* next;
};
struct Union_head
{
	Union_struct* first;
	Union_struct* tail;
	int number;
};


class Graph
{
private:
	vector<Edge*> edge_arr;


private:
	void initGraph();
	void NodeLink();
	void addEdge(int id, int start, int end, float weight);
	//Krusal;
	void MAKE_SET(Union_head* *sethead);
	Union_head* FIND_SET(int num);//存在可以优化空间;
	void UNION(Union_head* node1, Union_head* node2);

	//Prim;
	void addEdge2(int id, int start, int end, float weight);
public:
	int vexNum;
	int edgeNum;
	ArcNode* head;
	Union_head* *sethead;
	static bool comp( Edge* a,  Edge* b);

public:
	void Prim();
	void Kruskal();
	Graph();
	~Graph();
};

