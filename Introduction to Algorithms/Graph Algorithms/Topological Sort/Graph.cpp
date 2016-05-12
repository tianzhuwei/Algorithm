#include "Graph.h"


void Graph::Kahn(){
	clock_t time=clock();
	int n=0;//用来记录输出的顶点的个数;
	int* stack;
	stack=new int[vexNum];
	int top=-1;
	Edge* p=NULL;
	for (int i=0;i<vexNum;++i)
	{//将入度为0的顶点入栈;
		if (head[i].incount==0)
		{
			stack[++top]=i;
		}
	}//for;

	while(top!=-1){
		n++;
		int temp1,temp2;
		temp1=stack[top--];
		p=head[temp1].firstEdge;
		while(p!=NULL){
			temp2=--(head[p->vexName].incount);
			if (temp2==0)
			{
				stack[++top]=p->vexName;
			}
			p=p->next;
		}//while;
	}//while;
	if (n==vexNum)
	{
		cout<<"success"<<endl;
	}else{
		cout<<"fail"<<endl;
	}

	time=clock()-time;
	cout<<"use Kahn topplogical sort time :"<<time<<endl;
}

void Graph::DFS(int v){
		head[v].visit=1;
		Edge* p=NULL;
		p=head[v].firstEdge;
		while(p!=NULL){///////////注意：必需不能存在环;
			if (head[p->vexName].visit==0)
			{		
				DFS(p->vexName);
			}
			p=p->next;
		}
		//采用头插法输出顶点;
		//在这里输出;
}

void Graph::Under_DFS(){
	clock_t time=clock();
	for (int i=0;i<vexNum;++i)
	{
		if (head[i].visit==0)
		{
			DFS(i);
		}
		
	}
	time=clock()-time;
	cout<<"under DFS topological sort use time "<<time<<endl;
}
/*
//方法一的读法要慢，大概是第二种方法的两倍时间;
void Graph::initGraph(){
	clock_t time =clock();
	//ifstream txt("E:/xmark.txt");
	ifstream txt("E:/uniprot150m.txt",ios::binary);
	string temp;
	int start,end;
	if (!txt)
	{
		cout<<"can not open the file!"<<endl;
	}else{
		txt>>vexNum;
		initArcNode();
		cout<<"number of vex is "<<vexNum<<endl;
		while(!txt.eof()){
			getline(txt,temp);
			if (temp=="#"||temp=="")
			{
				continue;
			}
			if (temp!="")
			{
				int pos=temp.find(" ",0);
				istringstream st(temp.substr(0,pos));
				st>>start;
				//cout<<start<<endl;
				istringstream stt(temp.substr(pos,temp.length()));
				stt>>end;
				//cout<<end<<endl;
				//得到边的两个顶点，将边添加到图中;
				dirGraph(start,end);//有向图;

				//nodirGraph(start,end);//无向图;
				//edgeNum++;
			}
		}
	}
	txt.close();
	cout<<"init Graph use time "<<time<<endl;
}
*/
void Graph::initGraph(){
//	clock_t time=clock();
	//ifstream txt("E:/xmark.txt");
	ifstream txt("E:/uniprot150m.txt");
	//ifstream txt("E:/test.txt");
	edgeNum=0;
	if(!txt){
		cout<<"can not open the file"<<endl;
	}else{
		int start,end;
		txt>>vexNum;
		cout<<"The number of vex is "<<vexNum<<endl;
		initArcNode();
		while(!txt.eof()){
			if (txt.fail())
			{
				break;
			}
			txt>>start>>end;
			dirGraph(start,end);
			edgeNum++;
		}
	}
	txt.close();
	cout<<"number of edges is "<<edgeNum<<endl;
//	time=clock()-time;
//	cout<<"init Graph use time "<<time<<endl;
}


void Graph::nodirGraph(int start,int end){

}

void Graph::dirGraph(int start,int end){
	Edge* temp;
	temp=new Edge;
	temp->vexName=end;
	temp->next=head[start].firstEdge;
	head[start].firstEdge=temp;
	head[end].incount++;
}

void Graph::initArcNode(){
	head=new ArcNode[vexNum];
	for(int i=0;i<vexNum;++i){
		head[i].firstEdge=NULL;
		head[i].incount=0;
		head[i].visit=0;
	}
}

Graph::Graph(void)
{
	clock_t time=clock();
	initGraph();
	time=clock()-time;
	cout<<"creat Graph use time : "<<time<<endl;
}


Graph::~Graph(void)
{
	Edge* temp;
	for (int i=0;i<vexNum;++i)
	{
		
		while(head[i].firstEdge!=NULL){
			temp=head[i].firstEdge;
			head[i].firstEdge=temp->next;
			delete temp;
		}
	}
	delete[] head;
}


void Graph::readfile(){
	clock_t time=clock();
	//ifstream my("E:/xmark.txt");
	ifstream my("E:/uniprot150m.txt");
	//ifstream my("E:/test.txt");

//方法一
/*
	my>>vexNum;
	int f1,f2;
	while (!my.eof())
	{
		my>>f1>>f2;
		if(my.fail())
		{
			break;
		}
		//cout<<f1<<" "<<f2<<endl;
	}
	time=clock()-time;
	cout<<"success! use time :"<<time<<endl;
	my.close();
*/

//方法二
	/*
	if (my)
	{
		clock_t time=clock();
		string t;
		my.seekg(0,my.end);
		int length=my.tellg();
		my.seekg(0,my.beg);
		char * buffer =new char[length];
		//memset(buffer,0,length*sizeof(char));
		memset(buffer,0,length);
		cout<<"reading "<<length<<endl;
		my.read(buffer,length);
		//sprintf(buffer,buffer+'\n');
		if (my)
		{
			t=buffer;
			//cout<<"success"<<endl;
		}else{
			t=buffer;
		//	cout<<"fail!"<<endl;
		}

		int pos1=0,pos2=0;
	
		pos2=t.find("\n",0);
		istringstream vv(t.substr(pos1,pos2));
		vv>>vexNum;
		cout<<"number of vex "<<vexNum<<endl;
		initArcNode();
		string start,end;
		int s,e;
		while(t.find("\n",pos2)!=-1){
			pos1=t.find(" ",pos2++);
			start=t.substr(pos2,pos1-pos2);
			//cout<<start<<endl;
			pos2=t.find("\n",pos2);
			end=t.substr(++pos1,pos2-pos1);
			//cout<<end<<endl;
			//cout<<start<<" "<<end<<" ";
			istringstream ss(start);
			ss>>s;
			istringstream ee(end);
			ee>>e;
			dirGraph(s,e);
		}
		//cout<<t<<endl;
		//cout<<t.find("\n",0);
		time=clock()-time;
		cout<<" use time "<<time<<endl;
	}
	*/
}