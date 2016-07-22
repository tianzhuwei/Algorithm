#pragma once
#include<iostream>
#include<string>
using namespace std;
struct Node
{
	Node* suffixNode;//指向后缀结点;
	Node* alph[27];
	string words;

	Node() {
		for (int i = 0; i < 27; i++)
			alph[i] = NULL;
		suffixNode = NULL;
	}
};
struct ActivePoint {
	Node* point;
	int length;
	Node* index;
};
class SuffixTree
{
public:
	Node root;
	string myWords;
public:
	void bulid(string s);
	SuffixTree();
	~SuffixTree();
private:
	ActivePoint activePoint;
	int reminder;
private:
	bool find(char word);
	void innerSplit(int position,Node* prefixNode);
};

