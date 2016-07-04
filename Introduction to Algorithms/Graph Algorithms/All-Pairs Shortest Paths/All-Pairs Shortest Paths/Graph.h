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
	int const MAX = 99999;
	vector< vector<int> >A;//
	vector< vector<int> >Path;//;
	int nodeNum, edgeNum;
	double**L;
	double**temp;
private://私有函数;
	void readfile();
	void Init_A_Path();
	void W_L();
public://公共的变量;
	//vector<vector<double>> GraphHead;//采用矩阵的结构存储图;
	double* *a;//二维数据;
public://公共的函数;
	void Floyd();
	void Juzhenchengfa();
	Graph();
	~Graph();
};
