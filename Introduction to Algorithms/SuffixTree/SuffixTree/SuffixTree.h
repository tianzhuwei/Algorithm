#pragma once
#include<iostream>
#include<string>
using namespace std;

struct EdgeNode;
struct Node {//结点结构;
	EdgeNode* alph[27];//前26个表示字母 ，每27个表示一个特殊字符;
	Node* suffixNode;
	Node() {
		this->suffixNode = NULL;
		for (int i = 0; i < 26; i++)
			alph[i] = NULL;
	}
};
struct active {
	Node* active_node;
	EdgeNode* active_edge;
	int active_length;
};
struct EdgeNode {//边结点结构;
	int startNum;
	int endNum;
	Node* nextNode;
	EdgeNode() {
		startNum = 0;
		endNum = 0;
		nextNode = NULL;
	}
};
class SuffixTree
{
public:
	string words;
	Node head;
public:
	SuffixTree();
	~SuffixTree();
	Node InitSuffixTree();//初始化一个空 后缀树，也就浊说只有一个头结点;
private:
	bool find(char word);//用来查找当前活动结点是否都在字符“a”;
	void addChar(Node* head,string content);
	void innerSplit(int position, Node* prefixNode);//  innerSplit(chars, currenctIndex, splitNode);
private:
	active activePoint;//一个活动点的三元数组;

	int reminder;	//在每个步骤开始时剩余后缀的总数总是设置为1，它的意义是我们主动插入到每一步骤末尾的后缀数目是1（总是最后一个字符）;
};