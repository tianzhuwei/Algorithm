#include "SuffixTree.h"

SuffixTree::SuffixTree()
{
	activePoint.point = &root;
	activePoint.index = NULL;
	activePoint.length = 0;
	reminder = 0;
}

bool SuffixTree::find(char word)
{
	Node*start = activePoint.point;
	Node* current = activePoint.index;
	bool exist= false;
	if (current==NULL)//如果当前活动边为空，则查看活动结点的孩子结点;
	{
		if (start->alph[word-'A']!=NULL)
		{
			activePoint.index = start->alph[word-'A'];
			activePoint.length++;
			exist = true;
		}
	}
	else if(word==current->words[activePoint.length])//当前活动边不为空,则在活动边上进行查找;
	{
		activePoint.length++;
		exist = true;
		int a = (current->words).length();
		if (a==activePoint.length)//如果活动边长度已经达到最后一个字符，则将	活动边置为新的活动占;
		{
			activePoint.point = current;
			activePoint.index = NULL;
			activePoint.length = 0;
		}
	}
	else
	{
		exist = false;
	}
	return exist;
}

void SuffixTree::bulid(string str)
{
	myWords = str;
	int index = 0;
	int teleng= (myWords.length());
	for (; index < teleng; index++)
	{
		//获取要插入的字符;
		char word = myWords[index];
		if (find(word))//活动边是否有当前字符;
		{
			reminder++;
			continue;
		}
		if (reminder==0)//如果没有查找到，且待插入结点个数为0，则直接插入即可;
		{
			Node* te = new Node;

			//修改;
			//string s(myWords, index);
			(te->words) = (myWords, index,teleng);
			
			activePoint.point->alph[te->words[0]-'A'] = te;
		}
		else//如果reminder>0,需要进行分割;
		{
			Node* splitNode = activePoint.index;
			//要分割的边为当前的活动边;
			Node* te = new Node;
			//string s(activePoint.index->words, activePoint.length);
			//te->words = s;
			(te->words)=(activePoint.index->words, activePoint.length);
			activePoint.index->alph[(te->words)[0]-'A'] = te;
			//string ss(activePoint.index->words, 0, activePoint.length);
			//activePoint.index->words =ss;
			activePoint.index->words = (activePoint.index->words, 0, activePoint.length);
			Node* newnode = new Node;
			//string sss(myWords, index);//插入新的结点;
			(newnode->words) = (myWords, index,myWords.length());// sss;

			splitNode->alph[(newnode->words)[0] - 'A'] = newnode;

			//分割完成之后按照规则 1 2 进行处理;

			if (&root==activePoint.point)//如果活动顶点是根结点;
			{/*
			 1. 保留活动结点为根
			 2. 设置活动边为新插入的第一个字符
			 3. 活动长度减一！！！！！！！！！！！！！！！！！！！为什么没有体现出来
			 */
				//注意！！！
			}
			else if(activePoint.point->suffixNode==NULL)// 无后缀节点，则活动节点变为root
			{
				activePoint.point = &root;
			}
			else
			{
				// 否则活动节点变为当前活动节点的后缀节点
				activePoint.point = activePoint.point->suffixNode;
			}
			// 活动边和活动边长度都重置
			activePoint.index = NULL;
			activePoint.length = 0;
			// 递归处理剩余的待插入后缀
			innerSplit(index, splitNode);
		}
	}//for;
}

void SuffixTree::innerSplit(int position, Node* prefixNode)
{
	// 此处计算剩余待插入的后缀的开始位置
	//例如我们需要插入三个后缀(abx,bx,x)，已处理了abx，则还剩余ba和x，则下面计算的位置就是b的位置
	int start = position - reminder + 1;
	// dealStart表示本次插入我们需要进行查找的开始字符位置，因为由于规则2，可能出现通过后缀节点直接找到活动节点的情况
	// 如通过ab节点的后缀节点，直接找到节点b，那么此时的activePoint(node[b], null, 0)，我们需要从node[b]开始查找x，dealStart的位置就是x的位置
	int dealStart = start + activePoint.point->words.length() + activePoint.length;
	// 从dealStart开始查找所有后缀字符是否都存在(相对于活动点)
	for (int index = dealStart; index <= position; index++)
	{
		char w = myWords[index];
		if (find(w))//如果找到当前字符，则只是增加活动结点的长度;
		{
			continue;		
		}
		Node* splitNode = NULL;
		if (activePoint.index==NULL)//当前活动边为空，，只要在活动结点下插入一个结点;
		{
			Node* node = new Node;
			//string s(myWords,index);
			node->words = myWords, index;// s;
			activePoint.point->alph[node->words[0]-'A'] = node;
		}
		else//开始分割活动边;
		{
			splitNode = activePoint.index;
			Node* node = new Node;
			string s(splitNode->words,activePoint.length);
			node->words = splitNode->words, activePoint.length;// s;
			splitNode->alph[node->words[0] - 'A'] = node;
			for (int i = 0; i < 27; i++)
				node->alph[i] = splitNode->alph[i];
			splitNode->suffixNode = NULL;
			Node* newnode = new Node;
			//string ss(myWords, index);
			newnode->words = myWords, index;// ss;
			splitNode->alph[newnode->words[0] - 'A'] = newnode;
			//string sss(splitNode->words,0,activePoint.length);
			splitNode->words = splitNode->words, 0, activePoint.length;// sss;
			prefixNode->suffixNode = splitNode;//
		}
		reminder--;
		if (activePoint.point==&root)
		{

		}
		else if (activePoint.point->suffixNode==NULL)
		{
			activePoint.point = &root;
		}
		else
		{
			activePoint.point = activePoint.point->suffixNode;
		}

		activePoint.index = NULL;
		activePoint.length = 0;
		if (reminder>0)
		{
			innerSplit(position, splitNode);
		}
	}
}

SuffixTree::~SuffixTree()
{
}
