#pragma once
#include<iostream>

using namespace std;

struct node
{
	bool mark;//当前结点是否组成一个字符;
	node**child;//用一个数组存储孩子的位置指针;
	char alphabet;
	int num;
	node() {
		mark = false;
		child = new node*[26];
		alphabet = NULL;
		num = 0;
		for (int i = 0; i < 26; i++)
		{
			child[i] = NULL;
		}
	}
};
class Trie
{
public:
	node* MakeTrie();//初始化一棵字典树;
	void Insert(node* T,const char* a);//添加一个字符串;
	void Delete(node* T,const char* a);//删除一个字符串;
	node* search(node* T, const char* a);
	Trie();
	~Trie();
};

