#include "RTree.h"
#include<math.h>
RTree::RTree()
{
	M = 4;
	(M % 2 == 0) ? (m = M / 2) : (m = M / 2 + 1);//根据 M 来求得 m ;
	Root = new Node;
}

Node* RTree::ChooseLeaf(Rectangle re)
{
	Node* T = Root;
	if (T->child.size()==0||T->child[0].child==NULL)//如果T是叶子结点，则直接返回;
		return T;

	double area_suit;
	double area_current;
	Node* suit;
	while (T->child[0].child!=NULL)//没有孩子结点时即为叶子结点;
	{
		suit = T->child[0].child;//用来保存目前找到的最适合的结点指针,初始将第一个孩子设为最好;
		area_suit = areaIncrease(suit->region, re);
		int te = (T->child).size();
		for (int i = 0; i <te; i++)
		{
			//[选择子树] 如果N不是叶子结点，则遍历N中的结点
			//找出添加E.I时扩张最小的结点，并把该结点定义为F。
			//如果有多个这样的结点，那么选择面积最小的结点。
			area_current = areaIncrease(T->child[i].region, re);
			if (area_suit > area_current)//;
			{
				suit = T->child[i].child;
				area_suit = areaIncrease(suit->region, re);
			}
			else if (area_suit == area_current)//如果增长的面积一样，就选择总面积小的;
			{
				if (area_compute(suit->region, re) > area_compute(T->child[i].region, re))
				{
					suit = T->child[i].child;
					area_suit = areaIncrease(suit->region, re);
				}
			}//else;
		}//for;
		T = suit;
	}
	return T;
}

inline double RTree::areaIncrease(Rectangle r1, Rectangle r2)
{
	double old_area = (r1.rightPoint_x - r1.leftPoint_x)*(r2.rightPoint_y - r2.leftPoint_y);
	double new_area = area_compute(r1, r2);
	return (new_area - old_area);
}

inline double RTree::area_compute(Rectangle r1, Rectangle r2)
{
	double x1, x2, y1, y2;
	r1.leftPoint_x > r2.leftPoint_x ? (x1 = r2.leftPoint_x) : (x1 = r1.leftPoint_x);
	r1.leftPoint_y > r2.leftPoint_y ? (y1 = r2.leftPoint_y) : (y1 = r1.leftPoint_y);

	r1.rightPoint_x > r2.rightPoint_x ? (x2 = r1.rightPoint_x) : (x2 = r2.rightPoint_x);
	r1.rightPoint_y > r2.rightPoint_y ? (y2 = r1.rightPoint_y) : (y2 = r2.rightPoint_y);
	double area = (x2 - x1)*(y2 - y1);
	return area;
}

inline void RTree::changeRegion(Rectangle &r1, Rectangle r2)
{
	r1.leftPoint_x > r2.leftPoint_x ? (r1.leftPoint_x = r2.leftPoint_x) : (1);
	r1.leftPoint_y > r2.leftPoint_y ? (r1.leftPoint_y = r2.leftPoint_y) : (1);
	r1.rightPoint_x < r2.rightPoint_x ? (r1.rightPoint_x = r2.rightPoint_x) : (1);
	r1.rightPoint_y < r2.rightPoint_y ? (r1.rightPoint_y = r2.rightPoint_y) : (1);
}

void RTree::splitNode(Node* node)
{ 
	//	分裂原则：使得覆盖该新结点的矩形最小              重点注意！！！！！！！！！！！！关键
	//按我写的来说，孩子结点中的最后一个为最新插入的结点，保证最新结点构成的大矩形面积最小即可;
	if (node->parent==NULL)//如果当前结点是根结点，需要重新设置一个根结点;
	{
		Node* newroot = new Node;
		Node* split = new Node;
		split->child.push_back(node->child.back());
		node->child.pop_back();
		changeRegion(split->region, split->child.back().region);
		if (split->child.back().child!=NULL)
		{
			split->child.back().child->parent = split;//将孩子结点的父亲结点指向新的父亲;
		}
		childNode suit = node->child[0];
		while ((split->child.size()) < m) {
			int a=0;
			for (int i =0 ; i < m; i++) {
				if (area_compute(split->region,suit.region)>area_compute(split->region,node->child[i].region))
				{
					a = i;
					suit = node->child[i];
				}
			}//for;
			split->child.push_back(suit);
			changeRegion(split->region, split->child.back().region);
			if (split->child.back().child!=NULL)
			{
				split->child.back().child->parent = split;//将孩子结点的父亲结点指向新的父亲;
			}
			node->child.erase(node->child.begin() + a);	//将node 中的suit 删除;
		}//while;
		node->parent = newroot;
		//更新node 的regison 域
		node->region = node->child[0].region;
		for (int i = 1; i < node->child.size(); i++) {
			changeRegion(node->region, node->child[i].region);
		}

		//创建新的结点;
		split->parent = newroot;
		node->parent = newroot;
		Root = newroot;
		newroot->region = node->region;
		childNode te;
		te.child = node;
		te.region = node->region;
		newroot->child.push_back(te);

		te.child = split;
		te.region = split->region;
		newroot->child.push_back(te);
		changeRegion(newroot->region, te.region);

	}//if;
	else//如果分割的结点不是根结点;
	{
		/*
		将当前结点分割为两个结点，
		新增加一个split结点;并且将node 中的最后一个元素（最新插入的元素）插入到split中
		将split插入到父亲结点中
		*/
		Node* split = new Node;
		split->child.push_back(node->child.back());
		node->child.pop_back();
		changeRegion(split->region, split->child.back().region);
		if (split->child.back().child!=NULL)
		{
			split->child.back().child->parent = split;
		}
		childNode suit;
		while (split->child.size()<m)
		{
			int a=0;
			suit = node->child[0];
			//for (int i = 0; i < m; i++)
			for (int i = 0; i < node->child.size(); i++)// i 应该小于 node 结点中的个数
			{
				if (area_compute(split->region, suit.region) > area_compute(split->region, node->child[i].region))
				{
					a = i;
					suit = node->child[i];
				}
			}//for
			split->child.push_back(suit);
			changeRegion(split->region, split->child.back().region);
			if (split->child.back().child!=NULL)
			{
				split->child.back().child->parent = split;
			}
			node->child.erase(node->child.begin() + a);
		}//while;
		//更新node regison域；
		node->region = node->child[0].region;
		for (int i = 1; i < node->child.size(); i++)
		{
			changeRegion(node->region, node->child[i].region);
		}
		//将split结点加入到父亲结点;
		suit.child = split;
		suit.region = split->region;
		node->parent->child.push_back(suit);
		split->parent = node->parent;
		changeRegion(node->parent->region, split->region);

		//更新父亲结点的区域大小;
		updateRegion(node);
		updateRegion(split);

		//检查分裂之后造成父亲结点的元素个数增加，是否需要再进行分裂;
		if (node->parent->child.size()>M)
		{
			splitNode(node->parent);
		}
	}//else
}

void RTree::Insert(Rectangle re)
{
	Node* leafNode = ChooseLeaf(re);//找到要插入的叶子结点;
	//按我的思路就是先插入之后，再去判断是不是破坏了性质;
	childNode te;
	te.region = re;
	leafNode->child.push_back(te);
	//修改leafNode 的 region 域;
	changeRegion(leafNode->region, re);
	if ((leafNode->child.size())>M)//大于R树的阶数之后要进行分割;
	{
		splitNode(leafNode);
	}
	else
	{
		updateRegion(leafNode);
	}
}

inline bool RTree::RectangleEqual(Rectangle r1, Rectangle r2)//用来判断两个 矩形 是不是相同;
{
	if (r1.leftPoint_x!=r2.leftPoint_x||r1.leftPoint_y!=r2.leftPoint_y||r1.rightPoint_x!=r2.rightPoint_x||r1.rightPoint_y!=r2.rightPoint_y)
	{
		return false;
	}
	else
		return true;
}

void RTree::updateRegion(Node* node)// 当一个区域大小改变之后，依次更新父亲结点的区域大小;
{
	while (node!=NULL)
	{
		node->region = node->child[0].region;
		for (int i = 0; i < node->child.size(); i++)
		{
			changeRegion(node->region, node->child[i].region);
		}
		node = node->parent;
	}
}

void RTree::Condense(Node * LeafNode)
{
	if (LeafNode->child.size()<m)//如果当前结点孩子个数小于了 m ;
	{
		if (LeafNode==Root)//如果这个LeafNode 是根结点，要执行新的判断标准;
		{

		}//if
		else//非根结点，且孩子个数要小于 m ，则将 LeafNode结点加入一个栈Q中;
		{
			Q.push(LeafNode);//进入栈Q ，且删除在父亲结点中的位置;
			int i = 0;
			Node* parent = LeafNode->parent;
			while (parent->child[i].child!=LeafNode)
			{
				i++;
			}
			parent->child.erase(parent->child.begin()+i);

			Condense(parent);//因为LeafNode不是根结点，所以其父亲结点是一定存在的;

			//从 parent 的孩子中选出一个将LeafNode插入,有可能会造成分裂;
			childNode* temp=choseNodeToMerge(parent, Q.top());
			Q.pop();
			if (temp->child->child.size()>M)//如果插入之后个数大于 M 了，则还要对譔结点进行分裂操作;
			{
				splitNode(temp->child);//;
			}
		}//else

	}//if

}

childNode * RTree::choseNodeToMerge(Node * Parent, Node * mergeNode)
{
	int num = Parent->child.size();
	childNode suit=Parent->child[0];
	double inc = areaIncrease(suit.region, mergeNode->region);
	for (int i = 0; i < num; i++)
	{
		if (areaIncrease(Parent->child[i].region,mergeNode->region)<inc)
		{
			suit = Parent->child[i];
			inc = areaIncrease(suit.region, mergeNode->region);
		}
		else if (areaIncrease(Parent->child[i].region, mergeNode->region)==inc)
		{
			//取一个面积小的
			if (area_compute(suit.region,mergeNode->region)>area_compute(Parent->child[i].region,mergeNode->region))
			{
				suit = Parent->child[i];
			}
		}//elseif
	}//for
	return &suit;
}

void RTree::Delete(Rectangle re) 
{
	Node* leafNode = ChooseLeaf(re);//找到re 所在的叶子结点;
	//先删除 re ；
	bool ifExist = false;
	for (int i = 0; i < leafNode->child.size(); i++)
	{
		if (RectangleEqual(re,leafNode->child[i].region))
		{
			//删除re;
			ifExist = true;
			leafNode->child.erase(leafNode->child.begin() + i);
			updateRegion(leafNode);
			break;
		}
	}//for
	if (!ifExist)
	{
		cout << "can not find the re " << endl;
		return ;
	}

	//已经删除 re 但是没有更新 region 域;
	if (leafNode->child.size()<m)//如果结点的个数小于了m之后，需要将leafNode 剩余的结点重新插入;
	{
//			再回首已经是一个月了
/*
		这种情况比较复杂
		如果发现孩子个数不满足R树性质后，会将当前结点从R树中移走，加入一个链表中（要不要更新区域呢？更），一直找到满足性质或者找到根结点
		然后将链表中的结点与原先所在层中的结点合并
		这修好像很麻烦的样子

			下午回来再写
			常与同好争高低，不与傻X恩恩恩
*/

	}


}


RTree::~RTree()
{
}
