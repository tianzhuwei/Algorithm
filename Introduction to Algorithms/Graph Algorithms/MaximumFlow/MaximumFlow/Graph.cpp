#include "Graph.h"

void Graph::Init() //读取文件创建十字链表;
{
	fstream readfile("E:\\数据集\\最大流数据集\\2.txt");
	if (!readfile)
	{
		cout << "Can not open the file !" << endl;
		system("pause");
		exit(0);
	}
	string firstlevel;
	int vex_num = 0;
//	readfile >> firstlevel;
	getline(readfile, firstlevel);
	cout << firstlevel << endl;
	cout << "input the number of vex:";
	cin >> vex_num;
	cout << "input the souce node: ";
	cin >> souce_node;
	cout << "input the sinks_node: ";
	cin >> sinks_node;
	GraphHead.reserve(vex_num);

	for (int i = 0; i < vex_num; i++)
	{
		VexNode temp;
		temp.firstin = NULL;
		temp.firstout = NULL;
		GraphHead.push_back(temp);
		//GraphHead.at(i).firstin = NULL;
		//GraphHead.at(i).firstout = NULL;
	}
	while (!readfile.eof())
	{
		EdgeNode* edge_temp = new EdgeNode;
		readfile>>edge_temp->start_id;
		readfile >> edge_temp->end_id;
		readfile >> edge_temp->c;
		edge_temp->f = 0;
		edge_temp->nextin = NULL;
		edge_temp->nextout = NULL;//边结点信息加入完毕;

		if (readfile.fail())//用来判断末尾是否有空行;
			break;

		edge_temp->nextout=GraphHead.at(edge_temp->start_id).firstout ;//用来链接各个结点;
		GraphHead.at(edge_temp->start_id).firstout = edge_temp;
		edge_temp->nextin=GraphHead.at(edge_temp->end_id).firstin ;
		GraphHead.at(edge_temp->end_id).firstin = edge_temp;
	}//while;

	cout << "Read Over !" << endl;
}

int Graph::ifend() {//用来检查链表中的结点是否有残存容量;
	for (int i = 0; i < GraphHead.size()-2; i++)
	{
		if (e[link[i]] != 0)
			return link[i];
	}
	return -1;
}

void Graph::fenfaliuliang(int i )
{
	EdgeNode* temp1 = GraphHead.at(i).firstout;
	EdgeNode* temp2 = GraphHead.at(i).firstin;
	int nodeid;//用来存储与i号结点相关的联的那个结点;
	while (e[i]!=0)//只要 i号结点中有剩余流量就要进行分发;
	{
		//采用什么策略进行分发呢？;
		//按照高低顺序进行发放，从最低的开始;
		//最低并且还可以通过流量;
		if (temp1==NULL&&temp2==NULL)
		{
			//重新设置i号结点的高度;
			Relable(i);
			temp1 = GraphHead.at(i).firstout;
			temp2 = GraphHead.at(i).firstin;
			break;
		}
		if (temp1 != NULL) {
			nodeid = temp1->end_id;
		}
		else if(temp2!=NULL){
			nodeid = temp2->start_id;
		}
		if (h[i] = h[nodeid] + 1) {
			if (temp1!=NULL)
			{
				Push(i,temp1);
				temp1 = temp1->nextout;
			}
			else if(temp2!=NULL)
			{
				Push(i,temp2);
				temp2 = temp2->nextin;
			}
		}
	}//while;
}

void Graph::Relable(int i)
{

}

void Graph::Push(int st,EdgeNode* edge)
{
	//首先判断st 是边的起点还是终点;
	if (st==edge->start_id)//如果是起点;
	{
		if (edge->c-edge->f>e[st])//如果可以一次通过e[st];
		{
			edge->f = edge->f + e[st];
			e[edge->end_id] = e[edge->end_id] + e[st];
			e[st] = 0;
		}
		else
		{
			e[edge->end_id] = e[edge->end_id] + edge->c - edge->f;
			e[st] = e[st] - edge->c + edge->f;
			edge->f = edge->c;
		}
	}
	else //如果是终点则回退;
	{
		if (edge->f>e[st])
		{
			edge->f = edge->f - e[st];
			e[edge->start_id] = e[edge->start_id] + e[st];
			e[st] = 0;
		}
		else
		{
			e[st] = e[st] - edge->f;
			e[edge->start_id] = e[edge->start_id] + edge->f;
			edge->f = 0;
		}
	}
}

void Graph::Relabel_To_Front()
{
	//将h初始化;
	h = new int[GraphHead.size()];
//	memset(h, 0, GraphHead.size() * sizeof(int));
	e = new float[GraphHead.size()];//当前存放的流量的值是多少;
//	memset(h, 0, GraphHead.size() * sizeof(float));
	for (int i = 0; i < GraphHead.size(); i++)
	{
		h[i] = 0;
		e[i] = 0;
	}
	h[souce_node] = GraphHead.size() - 1;//源点的高度;
	link = new int[GraphHead.size() - 2];//初始化link表，用来存放除去 汇点和源点之外的所有点;
	for (int i = 0,j=0; i < GraphHead.size(); ++i) 
		if (i!=souce_node&&i!=sinks_node)
			link[j++] = i;

	EdgeNode* temp1= GraphHead[souce_node].firstout;
	while (temp1!=NULL)//预推送;将源点的出边全部推送；
	{
		temp1->f = temp1->c;
		e[temp1->end_id] = (temp1->c);
		temp1 = temp1->nextout;
	}
	temp1 = NULL;
	int i;

	while (1) {//如果Link里面还有残存的流量，ifend()返回顶点;

		i = ifend();
		if (i==-1)
		{
			break;
		}
			//将位于顶点i的残存容量分发出去,是全部分发出去，一点也不剩;
			int old = h[i];//i 号顶点的当前高度;
			EdgeNode* edge_temp=NULL;


			while (e[i] != 0) //只要边还有残存容量;
			{
				EdgeNode* temp2 = GraphHead.at(i).firstout;
				EdgeNode* temp3 = GraphHead.at(i).firstin;
				int min_high =-1;//用来存放最小高度的顶点;        可删除
				while(temp2!=NULL&&e[i]!=0)
				{
					int endid = temp2->end_id;
					if (h[endid]<h[i]&&temp2->f<temp2->c)
					{
						Push(i, temp2);//向endid号结点推送;
					}
					temp2 = temp2->nextout;
					//if ((temp2->f) < (temp2->c ))
					//{
					//	min_high = temp2->end_id;
					//	break;
					//}
				}
				while (temp3!=NULL&&e[i]!=0)
				{
					int startid = temp3->start_id;
					if (h[startid]<h[i]&&temp3->f>0)
					{
						Push(i, temp3);
					}
					temp3 = temp3->nextin;
				}
				if (e[i]!=0)
				{
					h[i]++;
				}
				/*
				while (temp2!=NULL)
				{
					if (temp2->f < temp2->c  && h[min_high]>=h[temp2->end_id])
					{
						min_high = temp2->end_id;
						edge_temp = temp2;
					}
					temp2 = temp2->nextout;
				}
				if (min_high==-1 && (temp3!=NULL))
				{
					while (temp3->f <= 0)
					{
						temp3 = temp3->nextin;
					}
					min_high = temp3->start_id;
					while (temp3!=NULL)
					{
						if (temp3->f > 0 && h[min_high]>=h[temp3->start_id] )
						{
							min_high = temp3->start_id;
							edge_temp = temp3;
						}
						temp3 = temp3->nextin;
					}
				}
				//目前找到可以传送的最低点;
					h[i] = h[min_high] + 1;
					if (i==edge_temp->start_id)//如果边是由 i -> min_high 方向;
					{
						if (e[i]>(edge_temp->c - edge_temp->f))
						{
							e[i] = e[i] - (edge_temp->c - edge_temp->f);
							e[edge_temp->end_id] = e[edge_temp->end_id] + (edge_temp->c - edge_temp->f);
							edge_temp->f = edge_temp->c;
						}
						else
						{
							edge_temp->f += e[i];
							e[edge_temp->end_id] += e[i];
							e[i] = 0;
						}
					}
					else// 边是由 min_high -> i 方向 ;
					{
						if (e[i]>edge_temp->f)
						{
							e[i] = e[i] - edge_temp->f ;
							e[edge_temp->start_id] = edge_temp->f;
							edge_temp->f = 0;
						}
						else
						{
							edge_temp->f = edge_temp->f - e[i];
							e[edge_temp->start_id] = e[i];
							e[i] = 0;
						}
					}
			*/	
			}		
			
			//修改这里后成为前置重贴标签方法;
			if (old!=h[i])//高度发生改变;
			{
				int j=0;
				while (link[j]!=i)//找到i 号结点在链表中的位置;
					j++;
				int tt = link[0];
				link[0] = link[j];
				link[j] = tt;
			}
	}//while(1);

	std::cout << "The maximum flow is " << e[sinks_node] << endl;
}

Graph::Graph()
{
	Init();
}


Graph::~Graph()
{
}
