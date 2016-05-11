#include "Graph.h"
#include <queue>
#include <vector>
#include <stack>
#include <time.h>
#include<cstdlib>
//广度优先搜索;这里使用的是STL中的queue来实现的队列，不知道会不会对速度产生影响，下面自定义队列来比较两者是否存在差异
  
void Graph::BFS(){
	clock_t time=clock();
	queue<int> qu;//用来存储结点的队列;
	//vector<int> test;//用来存储广度优先搜索的访问顺序;
	//if (head!=NULL)
	for(int i=0;i<vex_num;++i)
	{
		if (!head[i].statu)
			{
			qu.push(i);
			head[i].statu=true;
			Edge* temp;
			while(!qu.empty()){
				temp=head[qu.front()].next;//我们需要的是即将出队列的那个元素;
				qu.pop();
				//cout<<qu.back()<<endl;//.back()函数返回的值为队列中的最后一个;
				//	cout<<qu.front()<<endl;
				while(temp!=NULL){
					if (head[temp->vName].statu==false)//当前顶点没有被访问过，进入队列;
					{
						qu.push(temp->vName);
						head[temp->vName].statu=true;
					}
					temp=temp->nextEdge;
				}
			//	test.push_back(qu.back());
			}//while;
		}//if;
	}//for;
	time=clock()-time;
	cout<<"Complate! use time : "<<time<<endl;
	for (int i=0;i<vex_num;++i)
	{
		if (head[i].statu==false)
		{
			cout<<"BFS有问题！！！"<<i<<endl;
			system("pause");
		}
	}
}

void Graph::BFS_self(){
	clock_t time=clock();
	int* qu;
	qu=new int[vex_num+2];
	for (int i=0;i<vex_num;++i)
	{
		if (!head[i].statu)
		{
			Edge* temp;
			int j;//;
			int rear=0,front=0;
			rear=(rear+1)%vex_num;
			qu[rear]=i;
			head[i].statu=true;
			while(front!=rear){
				front=(front+1)%vex_num;
				j=qu[front];
				temp=head[j].next;
				while(temp!=NULL){
					if (!head[temp->vName].statu)
					{
						head[temp->vName].statu=true;
						rear=(rear+1)%vex_num;
						qu[rear]=temp->vName;
					}
					temp=temp->nextEdge;
				}
			}
	}
	}//for;
	delete[] qu;
	time=clock()-time;
	cout<<"BFS_self use time: "<<time<<endl;
	for (int i=0;i<vex_num;++i)
	{
		if (!head[i].statu)
		{
			cout<<i<<endl;
		}
	}
}

  //深度优先搜索递归;
void Graph::DFS_Sin(int v){
	Edge* e;
	head[v].statu=true;
	e=head[v].next;
	while(e!=NULL){
		if (!head[e->vName].statu)
		{
			DFS_Sin(e->vName);
		}
		e=e->nextEdge;
	}
}

void Graph::DFS_digui(){
	clock_t time=clock();
	for(int i=0;i<vex_num;++i){
		if (!head[i].statu)
		{
			DFS_Sin(i);
		}
	}
	time=clock()-time;
	cout<<"use DFS_digui time: "<<time<<endl;
}

void Graph::DFS_self(){
	clock_t time=clock();
	int* st;
	long big=2*edge_num;
	st=new int[big];
	int top=-1;
	for (int i=0;i<vex_num;++i)
	{
		if (!head[i].statu)
		{
			top++;
			st[top]=i;
			Edge * temp=NULL;
			while(top!=-1){
				if (!head[st[top]].statu)
				{
					head[st[top]].statu=true;
					temp=head[st[top]].next;
					top--;
					while(temp!=NULL){
						top++;
						st[top]=temp->vName;
						temp=temp->nextEdge;
					}//while
				}//if
				else{
					top--;
				}
			}//while
		}
	}
	time=clock()-time;
	cout<<"DFS非递归自定义栈方式耗时："<<time<<endl;
}
//深度优先搜索非递归;
void Graph::DFS(){
	clock_t time=clock();
	stack <int> st;
	for (int i=0;i<vex_num;++i)
	{
		if (!head[i].statu)//如果没有被访问过;
		{
			st.push(i);
			//head[i].statu=true;
			Edge* temp;
			while(st.empty()){
				if (!head[st.top()].statu)
				{
					head[st.top()].statu=true;
					temp=head[st.top()].next;
					st.pop();
					while(temp!=NULL){
						st.push(temp->vName);
					}
				}else{
					st.pop();
				}
			}//while;
		}//if;
	}//for;
	time=clock()-time;
	cout<<"DFS非递归STL栈方式耗时："<<time<<endl;
}

/*
void Graph::DFS(){
	clock_t time=clock();
	stack<int> st;
	for(int i=0;i<vex_num;++i){
		if (head[i].statu==false)
		{
			st.push(i);
			head[i].statu=true;
			Edge* temp;
			while(!st.empty()){
				//assert(st.top());	//使用cstdlib的头文件;
				temp=head[st.top()].next;//这种写法的时间消耗必定要长;
				///主要是就因为我们从栈中出来之后都是从当前顶点撒向的第一条边开始扫描的，
				///也就是说每条边我们都要访问多次，不仅仅是一次，所以在实际跑程序的时候消耗的时间要长的多久
				while(temp!=NULL && head[temp->vName].statu==true)
					temp=temp->nextEdge;
				if (temp==NULL)
				{
					st.pop();
				}else{
					head[temp->vName].statu=true;
					st.push(temp->vName);
				}
			}//while;
		}//if;
	}
	time=clock()-time;
	cout<<"DFS use time : "<<time<<endl;
	for(int i=0;i<vex_num;++i){
		if (!head[i].statu)
		{
			cout<<"DFS有问题！！"<<endl;
			system("pause");
		}
	}
}
*/


//用来测试读取txt文件的函数，仅仅是用来测试，在真正函数调用时并没有使用;
void Graph::read(){
// 	FILE * fp=fopen("E:/xmark.txt","r");
// 	fscanf(fp,"%d",&vex_num);
// 	cout<<"结点的个数："<<vex_num<<endl;
// 	//ArcNode* te;
// 	head=new ArcNode[vex_num];
// 	for (int i=0;i<vex_num;++i)
// 	{
// 		head[i].next=NULL;
// 	}
// 	//createVertexArry();
// 	int start,end;
// 	while(fscanf(fp,"%d",&start)!=EOF){
// 		fscanf(fp,"%d",&end);
// //		cout<<flush;
// 		//cout<<start<<" "<<end<<endl;
// 		//addedge_direction(start,end,0);
// 		Edge *e;
// 		e=new Edge;
// 		e->weight=0;
// 		e->vName=end;
// 		e->nextEdge=head[start].next;
// 		head[start].next=e;
// 	}
}

//用来创建一个无向图;
void Graph::creat_Linklist_Nodirection(){
	//ifstream read("E:/test.txt");
	//ifstream read("E:/xmark.txt");
	edge_num=0;
	ifstream read("E:/uniprot150m.txt");
	if (!read)
	{
		system("pause");
	}
	string tem;
	getline(read,tem);
	istringstream iss(tem);
	iss >> vex_num;
	cout<<"结点的个数："<<vex_num<<endl;
	createVertexArry();
	int start,end;
	int weight=0;

	//for(int i=0 ; i<edge_num;++i){
	while(!read.eof()){
		getline(read,tem);
		if (tem=="#")
		{
			continue;
		}
		if (tem!="")
		{
			int pos=tem.find(" ",0);
			istringstream st(tem.substr(0,pos));
			st>>start;
			//cout<<start<<endl;
			istringstream stt(tem.substr(pos,tem.length()));
			stt>>end;
			//cout<<end<<endl;
			addedge_nodirection(start,end,weight);
			edge_num++;
		}

	}
	read.close();
	cout<<"无向图链表存储完成！"<<endl;
	//inputvexnum();
	//createVertexArry();
	//inputedgenum();
	//addedgeinfo_nodirection();
}


//用来创建一个有向图;
void Graph::creat_Linklist_Direction(){
	//ifstream read("E:/xmark.txt");
	edge_num=0;
	ifstream read("E:/uniprot150m.txt");
	if (!read)
	{
		return;
	}
	string tem;
	getline(read,tem);
	istringstream iss(tem);
	iss >> vex_num;
	cout<<"结点的个数："<<vex_num<<endl;
	createVertexArry();
	int start,end;
	int weight=0;
	while(!read.eof()){
		getline(read,tem);
		if (tem=="#")
		{
			continue;
		}
		if (tem!="")
		{
			int pos=tem.find(" ",0);
			istringstream st(tem.substr(0,pos));
			st>>start;
			//cout<<start<<endl;
			istringstream stt(tem.substr(pos,tem.length()));
			stt>>end;
			//cout<<end<<endl;
			addedge_direction(start,end,weight);
			edge_num++;
		}
	}
	read.close();
	cout<<"有向图链表存储完成！"<<endl;

// 	inputvexnum();
// 	createVertexArry();
// 	inputedgenum();
// 	addedgeinfo_direction();
}

void Graph::addedgeinfo_nodirection(){
	int start,end,weight;
	for (int i=0;i<edge_num;++i)
	{
		cout<<"please input the start:"<<endl;
		cin>>start;

		cout<<"please input the end:"<<endl;
		cin>>end;

		cout<<"please input the weight:"<<endl;
		cin>>weight;
		addedge_nodirection(start,end,weight);
	}

}

void Graph::addedgeinfo_direction(){
	int start,end,weight;
	for (int i=0;i<edge_num;++i)
	{
		cout<<"please input the start:"<<endl;
		cin>>start;

		cout<<"please input the end:"<<endl;
		cin>>end;

		cout<<"please input the weight:"<<endl;
		cin>>weight;
		addedge_direction(start,end,weight);
	}

}

void Graph::addedge_direction(int start,int end,int weight){
	Edge* edge1;
	edge1=new Edge;
	edge1->weight=0;
	edge1->nextEdge=NULL; 
	edge1->vName=end;
	edge1->nextEdge=head[start].next;
	head[start].next=edge1;//采用头插法;
}

void Graph::addedge_nodirection(int start,int end,int weight){
	Edge* edge1;
	edge1=new Edge;
	edge1->weight=0;
	edge1->nextEdge=NULL; 
	edge1->vName=end;
	edge1->nextEdge=head[start].next;
	head[start].next=edge1;//采用头插法;

	Edge* edge2;
	edge2=new Edge;
	edge2->weight=0;
	edge2->nextEdge=NULL; 
	edge2->vName=start;
	edge2->nextEdge=head[end].next;
	head[end].next=edge2;//采用头插法;
}

void Graph::inputedgenum(){
	cout<<"please input the number of edge:"<<endl;
	cin>>edge_num;
}

void Graph::createVertexArry(){
	head=new ArcNode[vex_num];
	for (int i=0;i<vex_num;++i)
	{
		head[i].next=NULL;
		head[i].statu=false;
	}
}

void Graph::inputvexnum(){
	cout<<"please input the number of vex:"<<endl;
	cin>>vex_num;
}

Graph::Graph(void)
{
	head=new ArcNode;
	vex_num=0;
}

Graph::~Graph(void)
{
	for (int i=0;i<vex_num;++i)
	{
		Edge* tem;
		while(head[i].next!=NULL){
			tem=head[i].next;
			head[i].next=tem->nextEdge;
			delete tem;
		}
	}
	delete[] head;
}

