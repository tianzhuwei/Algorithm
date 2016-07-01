#include "Graph.h"

void Graph::readfile() {
	//string filename="E:\\new_data\\weightest.txt";
	string filename = "E:\\new_data\\OLRoad.txt";
	ifstream readfile(filename);
	if (!readfile)
	{
		cout << "Can not open the file ! " << endl;
		system("pause");
		exit(0);
	}
	int nodeNum, edgeNum;
	readfile >> nodeNum;//首先获取 图的  顶点个数  和  边数;
	readfile >> edgeNum;
	GraphHead.reserve(nodeNum);//为头结点链表分配 nodeNum 个空间;
	EdgeNode edgetemp;
	int start,outputdegree;
	char douhao;
	while (!readfile.eof())
	{
		readfile >> start;
		readfile >> outputdegree;
		if (readfile.fail())
			break;
		vector<EdgeNode>*vetemp=new vector<EdgeNode> ;
		for (int i = outputdegree; i >0 ; --i)
		{
			readfile >> edgetemp.end;
			readfile >> douhao;
			readfile >> edgetemp.weight;
			(*vetemp).push_back(edgetemp);
		}
		GraphHead.push_back(vetemp);
	}
}

Graph::Graph()
{
	cout << "Start read ..."<<endl;
	clock_t time = clock();
	readfile();
	time = clock() - time;
	cout << "Read Over ! use time "<<time<<" ms" << endl;
}

void Graph::Dijkstra() {
	int MAX = 99999;
	int S = 0;
	//cout<<"输入源点 S 标号 ： "<<endl;
	//cin>>S;
	double* dis		= new double[GraphHead.size()];//用来存储源点S到该数组下标结点的距离，初始情况为无穷，S处为0;
	for (int i = 0; i < GraphHead.size(); ++i)
		dis[i] = MAX;
	int* path	= new int[GraphHead.size()];//用来存储源点S到该数组下标结点的路径，也就是上一个结点是哪一个，初始值为 -1 ;
	bool* set		= new bool[GraphHead.size()];//用来标记该数组下标结点是否已经并入最短路径，初始为0，S处为1;
	vector<EdgeNode>* tem;
	for (int i = 0; i < GraphHead.size(); i++)
	{
		if (i==S)
		{
			tem = GraphHead.at(i);
			for (int j = 0; j < tem->size(); ++j) {
				dis[tem->at(j).end] = tem->at(j).weight;
				path[tem->at(i).end] = i;
			}
		}
		set[i]		= 0;
		path[i] = -1;
	}//for;
	set[S] = 1;
	dis[S] = 0;
	int u;//用来记录最小值;
	double min;
	for (int i = 0; i < GraphHead.size(); ++i) {
		min = MAX;
		
		for (int j = 0; j < GraphHead.size(); ++j) {
			if (set[j] == 0 && dis[j] < min)
			{
				u = j;
				min = dis[j];
			}//if;
		}
				set[u] = 1;
				tem = GraphHead.at(u);
				//for (int j = 0; j < GraphHead.size(); ++j) {
				for (int j = 0; j < tem->size(); j++)
				{
					if (dis[tem->at(j).end] > dis[u]+tem->at(j).weight)
					{
						dis[tem->at(j).end] = tem->at(j).weight;
						path[j] = i;
					}
				}
		}//for;
	}

void Graph::BellmanFord() {
	//初始化;
	//松弛操作;
	//检查负权回路;
	int MAX = 99999;
	int S = 0;
	//cout << "输入源点 S " << endl;
	//cin >> S;
	//初始化;
	int *dis = new int[GraphHead.size()];
	for (int i = 0; i < GraphHead.size(); i++)
	{
		dis[i] = MAX;
	}
	dis[S] = 0;
	int *pre = new int[GraphHead.size()];
	memset(pre, -1, GraphHead.size());
	pre[S] = S;
	//松弛操作;
	vector<EdgeNode>* tem;
	for (int i = 0; i < GraphHead.size(); i++)
	{
		tem=GraphHead.at(i);
		int end;
		double weight;
		for (int j = 0; j < (tem->size()); ++j) {
			end = (*tem).at(j).end;
			weight = (*tem).at(j).weight;
			if (dis[end]>dis[i]+weight)
			{
				dis[end] = dis[i] + weight;
				pre[end] = i;
			}
		}
	}//for;
	//负权回路检查;
	for (int i = 0; i < GraphHead.size(); i++)
	{
		tem = GraphHead.at(i);
		int end;
		double weight;
		for (int j = 0; j < tem->size(); j++)
		{
			end = (*tem).at(j).end;
			weight = (*tem).at(j).weight;
			if (dis[end]>weight+dis[i])
			{
				cout << "该图存在负权回路！" << endl;
				break;
			}
		}
	}//for
	int path = 100;
//cout << "输入目标点 " << endl;
//	cin >> path;
	while (S!=pre[path])
	{
		cout << path << " ";
		path = pre[path];
	}
	if (S==pre[path])
	{
		cout << S << " ";
	}
}


Graph::~Graph()
{
	for (size_t i = 0; i < GraphHead.size(); i++)
	{
		GraphHead.at(i)->~vector();
	}
	GraphHead.~vector();
}
