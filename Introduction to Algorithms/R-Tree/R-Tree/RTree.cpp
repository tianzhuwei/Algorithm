#include "RTree.h"
#include<math.h>
RTree::RTree()
{
	M = 4;
	(M % 2 == 0) ? (m = M / 2) : (m = M / 2 + 1);
	Root = NULL;
}


Node* RTree::ChooseLeaf(Rectangle re)
{
	Node* T = Root;
	if (T->child.size()==0)//如果T是叶子结点，则直接返回;
		return T;
	Node* suit=T->child[0].child;//用来保存目前找到的最适合的结点指针,初始将第一个孩子设为最好;

	for (int i = 1; i < T->child.size(); i++)
	{

	}
}

void RTree::Insert(Rectangle re)
{
	
}


RTree::~RTree()
{
}
