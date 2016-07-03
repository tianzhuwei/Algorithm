#include "Graph.h"

void Graph::Init() 
{
	fstream readfile("E:\\最大流数据集\\5.txt");
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
}

int Graph::ifend() {
	for (int i = 0; i < GraphHead.size()-2; i++)
	{
		if (e[link[i]] != 0)
			return link[i];
	}
	return -1;
}

void Graph::Relabel_To_Front()
{
	//将h初始化;
	h = new int[GraphHead.size()];
//	memset(h, 0, GraphHead.size() * sizeof(int));
	e = new float[GraphHead.size()];
//	memset(h, 0, GraphHead.size() * sizeof(float));
	for (int i = 0; i < GraphHead.size(); i++)
	{
		h[i] = 0;
		e[i] = 0;
	}
	h[souce_node] = GraphHead.size() - 1;//源点的高度;
	link = new int[GraphHead.size() - 2];//初始化link表;
	for (int i = 0,j=0; i < GraphHead.size(); ++i) {
		if (i!=souce_node&&i!=sinks_node)
		{
			link[j++] = i;
		}
	}

	EdgeNode* temp1= GraphHead[souce_node].firstout;;
	while (temp1!=NULL)//预推送;
	{
		temp1->f = temp1->c;
		e[temp1->end_id] = (temp1->c);
		temp1 = temp1->nextout;
	}
	int i;
	while (1) {//如果Link里面还有残存的流量，ifend()返回顶点;
		i = ifend();
		if (i==-1)
		{
			break;
		}
			//将位于顶点i的残存容量分发出去,是全部分发出去，一点也不剩;

			int old = h[i];
			EdgeNode* edge_temp=NULL;
			while (e[i] != 0) 
			{
				EdgeNode* temp2 = GraphHead.at(i).firstout;
				EdgeNode* temp3 = GraphHead.at(i).firstin;
				int min_high =-1;//用来存放最小高度的顶点;
				while(temp2!=NULL)
				{
					if ((temp2->f) < (temp2->c ))
					{
						min_high = temp2->end_id;
						break;
					}
					temp2 = temp2->nextout;
				}
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
				}
		
			//修改这里后成为前置重贴标签方法;
			if (old!=h[i])//高度发生改变;
			{
				int j=0;
				while (link[j]!=i)
				{
					j++;
				}
				int tt = link[0];
				link[0] = link[j];
				link[j] = tt;
			}
	}
	cout << "The maximum flow is " << e[sinks_node] << endl;
}

Graph::Graph()
{
	Init();
}


Graph::~Graph()
{
}
