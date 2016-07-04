#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<time.h>
using namespace std;
struct EdgeNode {
	int end;
	double weight;
};

class Graph
{
private://私有变量;
	int *dis;
private://私有函数;
	void readfile();
public://公共的变量;
	//ArcNode* GraphHead;
	vector<vector<EdgeNode>*> GraphHead;
public://公共的函数;
	void BellmanFord(int S);
	void Dijkstra(int S);
	void Johnson();
	Graph();
	~Graph();
};
