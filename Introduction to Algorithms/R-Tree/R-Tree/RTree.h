#pragma once
#include<iostream>
#include<vector>
using namespace std;

struct Rectangle//注意一下拷贝函数的问题;！！！！！！！！！！！！！！！！！！！！！！！！！！！！
{
	int leftPoint_x;
	int leftPoint_y;
	int rightPoint_x;
	int rightPoint_y;
	Rectangle() {
		leftPoint_x = 0;
		leftPoint_y = 0;
		rightPoint_x = 0;
		rightPoint_y = 0;
	}
};

struct Node;
struct childNode
{
	Rectangle region;
	Node* child;
	childNode() {
		child = NULL;
	}
};

struct Node
{
	Rectangle region;
	vector<childNode> child;
	Node* parent;
	Node() {
		parent = NULL;
	}
};

class RTree
{
public:
	int M;//M 阶R树;
	int m;//M 阶R树的内结点最少的元素个数，M/2 向上取整;
	Node * Root;//R树的根结点;
public:
	void Insert(Rectangle re);//向R树添加一个区域;
	void Delete(Rectangle re);//删除R树中的一个区域;
	RTree();
	~RTree();
private:
	Node* ChooseLeaf(Rectangle re);//返回要插入的叶子结点;
	inline int areaIncrease(Rectangle r1,Rectangle r2);//当r1 添加上 r2 时面积增加多少;
	inline int area_compute(Rectangle r1, Rectangle r2);//计算r1 和r2 两个矩形构成的MBR的面积;
	inline void changeRegion(Rectangle& r1 ,Rectangle r2);//当添加r2后，修改r1的 region 域;
	void splitNode(Node* node);
	inline bool RectangleEqual(Rectangle r1, Rectangle r2);
	void updateRegion(Node* node);
};

