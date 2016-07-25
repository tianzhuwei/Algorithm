#pragma once
#include "Graph.h"
#include<iostream>
#include<vector>
#include<fstream>
#include<string>
using namespace std;

struct EdgeNode
{
	int start_id;
	int end_id;
	float f;//流过 流量大小;
	float c;//边的可通过最大流量;
	EdgeNode* nextout;//指向具有相同头结点的狐;
	EdgeNode* nextin;//指向具有相同终结点的狐;
};

struct VexNode
{
	EdgeNode* firstin;//第一条指向该顶点的边;
	EdgeNode* firstout;//该顶点的第一条出边;
};

class Graph//图的存储采用十字链表的存储结构;
{
public:
	vector<VexNode>GraphHead;
public:
	void Relabel_To_Front();
	Graph();
	~Graph();

private:
	int* h;//用来存储每个结点的当前高度;
	float* e;//用来存放顶点的超额流的大小;
	int souce_node;//源结点；
	int sinks_node;//汇点;
	int* link;//链表;
	int ifend();//判断link表中是否有残存的流量，没有返回-1，否则返回 下标;
private:
	void Init();
	void fenfaliuliang(int i);//将i号结点的流量，发放到相邻的结点中去;
	void Relable(int i);//对i号结点重新设置高度,新的高度为最低高度加1;
	void Push(int st,EdgeNode* edge);//从st 顶点进行推送;
};

