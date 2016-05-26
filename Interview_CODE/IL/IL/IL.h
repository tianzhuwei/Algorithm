#pragma once
#include "Read.h"
#include "Node.h"
class IL:public Read
{
public:
	int*CO_lm;//左右匹配;
	int*CO_rm;

	int n;
	Node descendant_all;//用来全局存储descendant结果;
	Node lca_all;//用来存储全局lca结果;

//	int num;//用来对测试时的数据进行循环使用;
	CArray<int*,int*>* *S;//用来存储对应关键字id的数组指针;
	IL(void);
	~IL(void);
	void input();
	void output(int*v);
// 	int* rm(int v, CArray<int*,int*>* S2);//right match 右匹配 ,v代表先序遍历的一个int值,S2为关键字的一个集合;
// 	int* lm(int v ,CArray<int*,int*>*S2);//left match 左匹配,与右匹配相反，思路相差不多;
	void  descendant(Node &v1,Node &v2);
	void  lca(int*&v1,int*&v2);
	int IsAncestor(Node  &v1,Node  &v2);
	void Bubble(CArray<int*,int*>**S,int n);
	CArray<int*,int*>* get_slca(CArray<int*,int*>*&S1,CArray<int*,int*>*&S2);
	void testdata(CString data[32][7],int num);
	void lmANDrm(int v ,CArray<int*,int*>* &S2);
};

