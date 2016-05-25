#include "Graph.h"

void  Graph::NodeLink(){
	head = new ArcNode[vexNum];
	for (int i = 0; i < vexNum; i++)
	{
		head[i].firstEdge = NULL;
	}
}

void Graph::addEdge(int id, int start, int end, float weight){
	Edge* temp1;
	temp1 = new Edge;
	temp1->id = id;
	temp1->start = start;
	temp1->end = end;
	temp1->weight = weight;
	temp1->next = head[start].firstEdge;
	head[start].firstEdge = temp1;
	edge_arr.push_back(temp1);
	//temp2 = new Edge;
	//temp2->id = id;
	//temp2->start = end;
	//temp2->end = start;
	//temp2->weight = weight;
	//temp2->next = head[end].firstEdge;
	//head[end].firstEdge = temp2;
}

void Graph::addEdge2(int id, int start, int end, float weight){
	Edge* temp1,*temp2;
	temp1 = new Edge;
	temp1->id = id;
	temp1->start = start;
	temp1->end = end;
	temp1->weight = weight;
	temp1->next = head[start].firstEdge;
	head[start].firstEdge = temp1;

	temp2 = new Edge;
	temp2->id = id;
	temp2->start = end;
	temp2->end = start;
	temp2->weight = weight;
	temp2->next = head[end].firstEdge;
	head[end].firstEdge = temp2;
}

void Graph::initGraph(){

	string fileName="E:/California Road Network's Edges (Edge ID, Start Node ID, End Node ID, L2 Distance).txt";
	//string fileName = "E:/test-weight.txt";
	ifstream txt(fileName);
	if (!txt){
		cout << "Can not open the file!" << endl;
		exit(0);
	}
	int id, start, end;
	float weight;
	string Info;
	getline(txt, Info);
	cout << Info << endl;
	txt >> vexNum>>edgeNum;
	edgeNum = 0;
	NodeLink();
	while (!txt.eof())
	{
		txt >> id >> start >> end >> weight;
		//cout << weight << endl;
		//Krual用;
		//addEdge(id, start, end, weight);

		//Prim用;
		addEdge2(id, start, end, weight);
		edgeNum++;
		if (txt.fail()){
			break;
		}
	}//while;
	cout << "The graph have " << vexNum << "nodes and " << edgeNum << "edges" << endl;
}


bool Graph::comp(Edge* a, Edge* b){
	return a->weight < b->weight;
}
void Graph::MAKE_SET(Union_head* *sethead){
	for (int i = 0; i < vexNum ; i++)
	{
		Union_struct* u_s;
		u_s = new Union_struct;
		Union_head* u_s_head;
		u_s_head = new Union_head;

		u_s->next = NULL;
		u_s->vexnum = i;
		u_s->head = u_s_head;
		u_s_head->first=u_s;
		u_s_head->tail = u_s;
		u_s_head->number = 1;
		sethead[i] = u_s_head;
	}
}

Union_head* Graph::FIND_SET(int num){
	//return sethead[num]->first->vexnum;
	Union_struct* te;
	te = sethead[num]->first;
	return te->head;
}
void Graph::UNION(Union_head* node1, Union_head* node2){//将个数少的插入到个数多的;
	Union_head* big,* small;
	if (node1->number>=node2->number)
	{
		big = node1;
		small = node2;
	}
	else
	{
		big = node2;
		small = node1;
	}
	Union_head* big_head=FIND_SET(big->first->vexnum);
	Union_head* small_head = FIND_SET(small->first->vexnum);
	Union_struct* temp;
	temp = small->first;
	big_head->tail->next = small_head->first;
	big_head->tail = small_head->tail;
	while (temp != small_head->tail)
	{
		temp->head = big_head;
		big_head->number++;
		temp = temp->next;
	}
	big_head->number++;
	small_head->tail->head = big_head;
}
void Graph::Kruskal(){//选  边 形成并查集;
	/*
	sort( edge );按边的权值大小进行排序
	选取最小权值边添加到最小生成树（添加时要检查是否构成回路）
	使用并查集
	完成最小生成树
	读进来的文件中边的id并没有使用
	*/

	clock_t time = clock();
	sort(edge_arr.begin(),edge_arr.end(), comp );

	sethead = new Union_head*[vexNum];//用来存储每个顶点的并查集的位置;
	MAKE_SET(sethead);
	int CurrEdge = 0;
	int i = 0;//处理当前边，在排序好的edge_arr的边;
	while (CurrEdge!=vexNum-1)
	{
		Union_head* node1 = FIND_SET(edge_arr[i]->start);
		Union_head* node2 = FIND_SET(edge_arr[i]->end);
		i++;
		if (node1!=node2)
		{
			UNION(node1, node2);
			CurrEdge++;
			//cout << node1 << " " << node2 << endl;//用来输出最小生成树中一条边的两个顶点，只是一种表现形势;
		}//if
	}//while;
	time = clock() - time;
	cout << "Kruskal use time " << time <<"ms"<< endl;
}

void Graph::Prim(){//选  点  并入树;
	/*
	因为Prim算法是通过选取顶点来的，如果使用邻接链表的结构来存储的话，需要将两条边全部写出来，这点与Kruskal 算法不同，
	1、选定一个顶点开始
	2、选中与这个顶点相连的最小权值边，纳入树a中
	3、再次选出与这棵相连权值最小的边，纳入树a中
	*/
	//如何实现？
	clock_t Prime_time = clock();
	bool*visit;
	visit = new bool[vexNum];
	memset(visit, 0, vexNum*sizeof(bool));
	priority_queue<Edge>Youxian;

	//将与0号顶点相邻的边加入优先队列;
	visit[0] = 1;
	Edge* temp=head[0].firstEdge;
	Edge  ben;
	while (temp!=NULL)
	{
		//将temp加入优先队列，按权值大小;
		//ben.id=temp->id;
		//ben.start = temp->start;
		//ben.end = temp->end;
		//ben.next = temp->next;
		//ben.weight = temp->weight;
		ben = *temp;
		Youxian.push(ben);
		temp = temp->next;
	}
	int mark = 1;//用来记录当前已经并入的顶点的个数 ;
	while (mark<vexNum&& !Youxian.empty())
	{
		//从优先队列中选出权值最小的边;
		ben = Youxian.top();
		//删除这个顶点;
		Youxian.pop();
		//因这是双向边。所以要判断一下选中边是否已经存在最小树中;
		if (!visit[ben.end] || !visit[ben.start])//当前顶点没有在树中;
		{
			//cout<<新加边，此即为最小生成树的所有边;
			visit[ben.end]=1;
			visit[ben.start] = 1;
			mark++;
			temp = head[ben.end].firstEdge;
			while (temp != NULL)
			{
				//将temp加入优先队列，按权值大小;
				//ben.id = temp->id;
				//ben.start = temp->start;
				//ben.end = temp->end;
				//ben.next = temp->next;
				//ben.weight = temp->weight;
				ben = *temp;
				Youxian.push(ben);
				temp = temp->next;
			}
		}
	}

	Prime_time = clock() - Prime_time;
	cout << "Prime use time is " << Prime_time << endl;

}

Graph::Graph(){
	initGraph();
}
Graph::~Graph()
{
}
