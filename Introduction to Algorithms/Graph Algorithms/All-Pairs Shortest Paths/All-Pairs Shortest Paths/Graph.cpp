#include "Graph.h"

void Graph::readfile() {
	string filename = "E:\\new_data\\OLRoad.txt";
	ifstream readfile(filename);
	if (!readfile)
	{
		cout << "Can not open the file ! " << endl;
		system("pause");
		exit(0);
	}
	readfile >> nodeNum;//首先获取 图的  顶点个数  和  边数;
	readfile >> edgeNum;
	a=new double*[nodeNum];//为头结点链表分配 nodeNum 个空间;
	for (int i = 0; i < nodeNum; i++)
	{
		double *b = new double[nodeNum];
		for (int j = 0; j < nodeNum; j++)
		{
			if (i==j)
			{
				b[j] = 0;
			}
			else {
				b[j] = MAX;
			}
		}
		a[i] = b;
	}
//	EdgeNode edgetemp;
	int start,outputdegree,end_id;
	double weight;
	char douhao;
	while (!readfile.eof())
	{
		readfile >> start;
		readfile >> outputdegree;
		if (readfile.fail())
			break;
//		vector<EdgeNode>*vetemp=new vector<EdgeNode> ;
		for (int i = outputdegree; i >0 ; --i)
		{
			readfile >> end_id;
			readfile >> douhao;
			readfile >> weight;
			(a[start])[end_id] = weight;
		}
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

void Graph::Init_A_Path() {
	for (int i = 0; i < nodeNum; ++i) {
		vector<int>tempA;
		vector<int>tempPath;
		for (int j = 0; j < nodeNum; j++)
		{
			tempA.push_back(a[i][j]);
			tempPath.push_back(-1);
		}//for
		A.push_back(tempA);
		Path.push_back(tempPath);
	}
}

void Graph::Floyd()
{
	for (int k = 0; k < nodeNum; k++)
	{
		for (int i = 0; i < nodeNum; i++)
		{
			for (int j = 0; j < nodeNum; j++)
			{
				if (a[i][j]>a[i][k]+a[k][j])
				{
					a[i][j] = a[i][k] + a[k][j];
					Path[i][j] = k;
				}
			}
		}
	}
}

void Graph::W_L() {
	int min;
	for (int i = 0; i < nodeNum; i++)
	{
		min = a[i][0] + temp[0][i];
		for (int j = 0; j < nodeNum; j++) 
		{
			for (int k = 0; k < nodeNum; k++)
				if (min>a[i][k]+temp[k][j])
					min = a[i][k] + temp[k][j];
			L[i][j] = min;
		}
	}//for;

	//L -> temp;
	for (int i = 0; i < nodeNum; i++)
	{
		for (int j = 0; j < nodeNum; j++)
		{
			temp[i][j] = L[i][j];
		}
	}
}

void Graph::Juzhenchengfa() {
	L= new double*[nodeNum];
	temp = new double*[nodeNum];
	for (int i = 0; i < nodeNum; i++)
	{
		double*b = new double[nodeNum];
		double*tt = new double[nodeNum];
		for (int j = 0; j < nodeNum; j++)
		{
			b[j] = a[i][j];
			tt[j] = a[i][j];
		}
		L[i] = b;
	}
	for (int i = 1; i < nodeNum; i++)//执行nodenum 次;
	{
		W_L();
	}
}

Graph::~Graph()
{
}
