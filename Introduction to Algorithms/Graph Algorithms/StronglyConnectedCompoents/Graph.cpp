#include "Graph.h"

void Graph::initGraph(int num){
	//ifstream txt("E:/test.txt");
	string re[] = { "test.txt", "xmark.txt", "uniprot22m.txt", "uniprot100m.txt", "uniprot150m.txt" };
	string fileName = "E:/" + re[num];
	ifstream txt(fileName);
	if (!txt){
		cout << "Can not open the file, please check out the file !" << endl;
	}
	else
	{
		int start, end;
		txt >> vexNum;
		cout << "The number of vex is " << vexNum << endl;
		head = NULL;
		head = NodeLink();
		EdgeNum = 0;
		while (!txt.eof()){
			txt >> start >> end;
			if (txt.fail())
			{
				break;
			}//if;

			//cout << start << " " << end << endl;
			addDirEdge(head,start, end);
			EdgeNum++;//统计边的个数;
		}//while;
		cout << "The number of edge  is " << EdgeNum << endl;
	}
}


void Graph::addDirEdge(ArcNode* head1,int start, int end){
	Edge* temp;
	temp = new Edge;
	temp->VexName = end;
	//temp->next = NULL;
	temp->next = head1[start].firstEdge;
	head1[start].firstEdge = temp;
	(head1[end].inCount)++;
}

ArcNode* Graph::NodeLink(){
	ArcNode* head1;
	head1 = new ArcNode[vexNum];
	for (int i = 0; i < vexNum; ++i){
		head1[i].inCount = 0;
		head1[i].firstEdge = NULL;
	}
	return head1;
}

void Graph::Gabow_DFS(int num){
	G_visit[num] = 1;
	Path[++Path_Top] = num;
	Root[++Root_Top] = num;
	G_pre[num] = G_time++;
	Edge* temp = head[num].firstEdge;
	while (temp != NULL){
		if (G_visit[temp->VexName] == 0){
			Gabow_DFS(temp->VexName);
		}
		else if (G_mark[temp->VexName]==0){
			while (G_pre[temp->VexName] < G_pre[Root[Root_Top]]){
				Root_Top--;
			}
		}
		temp = temp->next;
	}//while;
	if (num== Root[Root_Top]){
		while (num != Path[Path_Top]){
			G_mark[Path[Path_Top]] = G_id;
			Path_Top--;
		}
		G_mark[Path[Path_Top--]] = G_id;
		Root_Top--;
		G_id++;
	}//if
}

void Graph::Gabow(){//本质为Tajan算法的一种改进;
	clock_t Gabow_Time = clock();
	Path = new int[vexNum];
	Root = new int[vexNum];
	G_mark = new int[vexNum];
	Path_Top = -1;
	Root_Top = -1;
	G_id = 1;
	G_time = 0;
	G_pre = new int[vexNum];
	G_visit = new bool[vexNum];
	memset(G_visit, 0, vexNum*sizeof(bool));
	for (int i = 0; i < vexNum; i++)
	{
		if (G_visit[i] == 0){
			Gabow_DFS(i);
		}
	}
	Gabow_Time = clock() - Gabow_Time;
	cout << "The  number of SCC is " << G_id-1 << endl;
	cout <<"Gabow Use time "<< Gabow_Time << endl;
}

void Graph::Kosaraju_Reverse(){

	Reverse_head=NodeLink();
	Edge* temp;
	for (int i = 0; i < vexNum; ++i){
		temp = head[i].firstEdge;
		while (temp != NULL){
			addDirEdge(Reverse_head, temp->VexName, i);
			temp = temp->next;
		}
	}//for;
}

void Graph::Kosaraju_DFS(int num){
	Edge* temp;
	temp = head[num].firstEdge;
	K_visit[num] = 1;
	while (temp != NULL)
	{
		if (K_visit[temp->VexName] == 0){
			Kosaraju_DFS(temp->VexName);
		}
		temp = temp->next;
	}
	//按访时间由小到大进栈;
	stack[++stack_top] = num;
}

void Graph::DFS(int begin){
	Edge* temp = NULL;
	temp=Reverse_head[begin].firstEdge;
	K_visit[begin] = 1;
	K_mark[begin] = K_id;
	while (temp!=NULL)
	{
		if (K_visit[temp->VexName]==0)
			DFS(temp->VexName);
		temp = temp->next;
	}
}

void Graph::Kosaraju(){//两次DFS，一次正向，一次反向;
	clock_t K_time = clock();
	K_mark = new int[vexNum];
	K_visit = new bool[vexNum];
	memset(K_visit, 0, vexNum*sizeof(bool));  
	K_id = 0;
	Kosaraju_Reverse();//求解反向图;
	stack_top = -1;
	for (int i = 0; i < vexNum; ++i){
		if (K_visit[i]==0)
			Kosaraju_DFS(i);//求出每个点的访问时间;
	}//for;
	//考虑是否可以去掉;
	for (int i = 0; i < vexNum; ++i)
		K_visit[i] = 0;
	//memset(visit, 0, vexNum*sizeof(bool));

	while (stack_top!=-1)
	{
		int i = stack[stack_top--];
		if (K_visit[i]==0)
		{
			DFS(i);
			K_id++;
		}
	}
	K_time = clock() - K_time;
	cout << "The number of StronglyConnectedCompents is " << K_id << endl;
	cout << "Kosaraju use time " << K_time << endl;
}

int Graph::min(int a, int b){
	if (a >= b)
		return b;
	else{
		return a;
	}
}

void Graph::Tarjan_DFS(int num){
	T_visit[num] = 1;
	ifInStack[num] = 1;
	stack[++stack_top] = num;
	DFN[num] = T_pre;
	LOW[num] = T_pre++;
	Edge* temp = head[num].firstEdge;
	while (temp != NULL){
		if (T_visit[temp->VexName]==0)
		{
			Tarjan_DFS(temp->VexName);
			LOW[num] = min(LOW[num], LOW[temp->VexName]);
		}
		else if (DFN[temp->VexName]<DFN[num] && ifInStack[temp->VexName])
		{
				LOW[num] = min(LOW[num], DFN[temp->VexName]);
		}
		temp = temp->next;
	}//while;
	if (DFN[num]==LOW[num])
	{
			while (stack[stack_top]!=num)
			{
				T_mark[stack[stack_top]] = T_id;
				ifInStack[stack[stack_top--]] = 0;
			}
			T_mark[stack[stack_top]] = T_id;
			ifInStack[stack[stack_top--]] = 0;
			T_id++;
	}//if;
}

void Graph::Tarjan(){//用一个stack,两个数组来操作;
	clock_t T_time = clock();
	DFN = new int[vexNum];
	LOW = new int[vexNum];
	T_mark = new int[vexNum];
	ifInStack = new bool[vexNum];
	T_visit = new bool[vexNum];	
	memset(T_visit, 0, vexNum*sizeof(bool));
	stack_top = -1;
	T_id = 0;
	T_pre = 0;
	for (int i = 0; i < vexNum; ++i){
		if (T_visit[i]==0)
			Tarjan_DFS(i);
	}
	T_time = clock() - T_time;
	cout << "The number of SCC is " << T_id << endl;
	cout << "Tarjan Use time " << T_time << endl;
}

Graph::Graph()
{
	cout << "use Graph( int num ) ! " << time << endl;
}

Graph::Graph(int num){
	clock_t time = clock();
	initGraph(num);
	stack = new int[vexNum];
	time = clock() - time;
	cout << "Creat Graph use time " << time << endl;
}

Graph::~Graph()
{
	for (int i = 0; i < vexNum; ++i){
		Edge* temp = NULL;
		while (head[i].firstEdge!=NULL){
			temp = head[i].firstEdge;
			head[i].firstEdge = temp->next;
			delete temp;
		}
	}
	delete[] head;
}
