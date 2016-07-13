#include "SuffixTree.h"

Node SuffixTree::InitSuffixTree() {
	words = "abcd";
	addChar(&head, words);
	return head;
}
bool SuffixTree::find(char word) {
	Node* currentNode = activePoint.active_node;
	EdgeNode* currentEdge = activePoint.active_edge;
	bool exist = false;
	if (currentEdge==NULL)//如果当前活动边为NULL的话;则从活动结点的子结点查找；
	{
		if (currentNode->alph[word-'A']!=NULL)
		{
			exist = true;
			activePoint.active_length++;
			activePoint.active_edge = currentNode->alph[word - 'A'];
		}//if
	}//if
	 //如果有活动边，则在活动边上查找 ;
	else if (words[currentEdge->startNum+activePoint.active_length]==word)//活动边在活动长度与指定的字符 word是否相同;
	{//上面注意一下;
		activePoint.active_length++;
		exist = true;
		if (activePoint.active_length==currentEdge->endNum)
		{// 如果活动边的长度已达到活动边的最后一个字符，则将活动点置为活动边，同时活动边置为null，长度置为0
			activePoint.active_node = currentEdge->nextNode;
			activePoint.active_edge = NULL;
			activePoint.active_length = 0;
		}
		else
		{
			exist = false;
		}
	}
	return exist;
}

void SuffixTree::innerSplit(int position, Node* prefixNode) {
	// 此处计算剩余待插入的后缀的开始位置
	//例如我们需要插入三个后缀(abx,bx,x)，已处理了abx，则还剩余ba和x，则下面计算的位置就是b的位置
	int start = position - reminder + 1;
	// dealStart表示本次插入我们需要进行查找的开始字符位置，因为由于规则2，可能出现通过后缀节点直接找到活动节点的情况
	// 如通过ab节点的后缀节点，直接找到节点b，那么此时的activePoint(node[b], null, 0)，我们需要从node[b]开始查找x，dealStart的位置就是x的位置
	//int dealStart = start + activePoint.point.chars.length + activePoint.length;
	int delstart=start+activePoint.active_length;//!!!!!!!!!!!!!!!!!!!!有问题注意
	for (int index = delstart; index <= position; index++) {
		if (find(words[position]))
		{
			continue;
		}
		Node* splitNode = new Node;
		EdgeNode *edge_temp = new EdgeNode;
		if (activePoint.active_edge==NULL)//说明没有找到活动边，那么只需要在活动节点下插入一个节点即可
		{
			activePoint.active_node->alph[words[position] - 'A'] = edge_temp;
			edge_temp->startNum = activePoint.active_length;
			edge_temp->endNum = activePoint.active_length + 1;
			edge_temp->nextNode = splitNode;
		}
		else
		{//开始分割;
			activePoint.active_edge->nextNode = splitNode;
			splitNode->alph[words[position]] = edge_temp;
			edge_temp->startNum = delstart;
			edge_temp->endNum = activePoint.active_edge->endNum;
			activePoint.active_edge->endNum = delstart - 1;
			prefixNode->suffixNode = splitNode;
		}
		reminder--;
		if (&head == activePoint.active_node)//如果活动结点是根结点的话;
		{
			/*
			1. 活动结点保留为根结点
			2. 设置活动边为
			*/
		}//按照规则3处理;
		else if (activePoint.active_node->suffixNode == NULL)// 无后缀节点，则活动节点变为root
		{
			activePoint.active_node = &head;
		}
		else
		{// 否则活动节点变为当前活动节点的后缀节点
			activePoint.active_node = activePoint.active_node->suffixNode;
		}//else;
		 // 活动边和活动边长度都重置
		activePoint.active_length = 0;
		activePoint.active_edge = NULL;
		//递归处理剩余的待插入后缀;
		if (reminder>0)//;如果reminder < 0 则不需要再进行分割
		{
			innerSplit(position, splitNode);
		}		
	}
}
void SuffixTree::addChar(Node* head, string words) {
	int position = 0;
	//对活动顶点进行初始化;
	activePoint.active_edge = NULL;//活动的边初始化为空边;
	activePoint.active_length = 0;//活动长度初始化为0;
	activePoint.active_node = head;//活动结点初始化为后缀树的根结点;

	//在每个步骤开始时剩余后缀的总数总是设置为1;  
	//我 日 啊 ，这么乱;什么中TM的“每一个步骤开始时总是设置为 0”
	reminder = 0;//初始化时边的个数为 0 个;
	for (; position < words.length(); ++position)//按从左到右的顺序将字符串中的字符添加到后缀树;
	{
		if (find(words[position]))//如果找到当前字符;
		{
			reminder++;
			continue;
		}
		// 不存在的话，如果reminder==0表示之前在该字符之前未剩余有其他带插入的后缀字符，所以直接插入该后缀字符即可
		if (reminder==0)
		{
			// 直接在当前活动节点插入一个节点即可
			Node* Nodetemp = new Node;
			EdgeNode* Edge_temp = new EdgeNode;
			Edge_temp->startNum = activePoint.active_length;
			Edge_temp->endNum = ++activePoint.active_length;
			activePoint.active_node->alph[words[position]-'A'] = Edge_temp;
		}
		else//如果	reminder > 0,说明该字符之前存在缓冲的字符串，需要进行分割;
		{
			// 待分割的节点即为活动边(active_edge);
			Node* node_temp = new Node;
			EdgeNode* edge_temp = new EdgeNode;
			edge_temp->endNum = activePoint.active_edge->endNum;
			edge_temp->startNum = activePoint.active_edge->startNum + reminder;
			edge_temp->nextNode = node_temp;
			activePoint.active_edge->nextNode = node_temp;
			node_temp->alph[words[position]-'A'] = edge_temp;

			// 分割完成之后需根据规则1和规则2进行区分对待
			// 按照规则1进行处理
			if (head==activePoint.active_node)//如果活动结点是根结点的话;
			{
				/*
				1. 活动结点保留为根结点
				2. 设置活动边为
				*/
			}//按照规则3处理;
			else if (activePoint.active_node->suffixNode==NULL)// 无后缀节点，则活动节点变为root
			{
				activePoint.active_node = head;
			}
			else
			{// 否则活动节点变为当前活动节点的后缀节点
				activePoint.active_node = activePoint.active_node->suffixNode;
			}//else;
			 // 活动边和活动边长度都重置
			activePoint.active_length = 0;
			activePoint.active_edge = NULL;
			//递归处理剩余的待插入后缀;
			innerSplit(position, node_temp);
		}//else
	}
	EdgeNode edge1;
	Node* node1=new Node;
	edge1.startNum = 0;
	edge1.endNum = position;
	edge1.nextNode = node1;
}

SuffixTree::SuffixTree()
{
}


SuffixTree::~SuffixTree()
{

}
