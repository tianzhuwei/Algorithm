#include "bPlus.h"

void bPlus::InsertSort(vector<int>* ve) {
	int max = ve->size();
	vector<int>::iterator end = ve->end();
	end--;
	vector<int>::iterator begin = ve->begin();
	for (; end > begin;end--) {
		if (*end < *(end-1))
		{
			swap(*end,*(end-1));
		}
	}
}

void bPlus::InitBplus() {
	head = new Node;
	m = 4;
	(m % 2 == 0 )?( min = m / 2 ):( min = m / 2 + 1);
}
void bPlus::changeBig(Node* node, int key) {
	int i = 0;
	while (node->parent->child->at(i) != node) 
		i++;
	node->parent->key->at(i) = key;
	if (node->parent->parent!=NULL)
	{
		changeBig(node->parent, key);
	}
}
void bPlus::addKey(int key) {
	if ( (head->child)->size()==0)//初始化时根结点就是叶子结点;
	{
		head->key->push_back(key);//插入关键字并且进行升序排序;
		InsertSort(head->key);
		if ((head->key)->size() <= m )//根结点个数小于  m  个时
		{
			return;
		}
		else//开始进行第一次分割;
		{
			//head->key->push_back(key);//插入关键字并且进行升序排序;
			//InsertSort(head->key);
			Node* first = new Node;
			Node*second = new Node;
			Node*newhead = new Node;
			first->key->assign((head->key)->begin(), (head->key)->begin() + min+1);
			second->key->assign((head->key)->begin() + min+1, (head->key)->end());
			first->next = second;
			first->parent = newhead;
			second->parent = newhead;
			second->pre = first;
			newhead->key->push_back(*((head->key)->begin() + min ));
			newhead->key->push_back(*((head->key)->end()-1));
			newhead->child->push_back(first);
			newhead->child->push_back(second);
			delete head;
			head = newhead;
		}
		return;
	}

	//当根元素插入满之后开始产生孩子结点;
	Node* current= search(key);//找到可以插入的叶子结点;
	//将 key 插入到查找到的叶子结点;
	current->key->push_back(key);
	InsertSort(current->key);
	if (key==current->key->back())//如果刚刚插入的元素大于当前结点的最大值，修改父亲结点的对应值;
	{
		changeBig(current, key);
		//int i = 0;
		//while (current->parent->child->at(i)!=current)
		//{
		//	i++;
		//}
		//current->parent->key->at(i) = key;
	}
	//当插入key之后，如果当前结点的个数大于了最大值 m ，我们需要对当前数组进行拆分;
	while (current->key->size() > m && current->parent!=NULL)
	{
		Node* first = new Node;
		Node*second = new Node;
		first->key->assign((current->key)->begin(), (current->key)->begin() + min+1);
//		first->child->assign((current->child)->begin(), (current->child)->begin() + min + 1);
		second->key->assign((current->key)->begin() + min+1, (current->key)->end());
//		second->child->assign((current->child)->begin() + min + 1, (current->child)->end());
		first->next = second;
		first->parent = current->parent;
		second->parent = current->parent;
		second->pre = first;
		if (current->pre!=NULL)
		{
			current->pre->next = first;
			first->pre = current->pre;
		}
		if (current->next!=NULL)
		{
			current->next->pre = second;
			second->next;
		}
		
		//将first中最大元素放到上一个结点中;
		Node* parent = current->parent;
		parent->key->push_back(first->key->back());
		parent->child->push_back(first);
		int position = parent->key->size();
		position--;
		for (;position>0;--position)
		{
			if (parent->key->at(position - 1)<=parent->key->at(position))
			{
				break;
			}else	{
				swap(parent->key->at(position), parent->key->at(position - 1));
				swap(parent->child->at(position), parent->child->at(position - 1));
			}
		}
		(parent->child)->at(position + 1) = second;
		if (current->child->size()!=0)//如果当前结点有孩子结点;
		{
		//	问题出在了创建新的结点代替满结点
		//	将孩子指针指向新的父亲结点
			int i = 0;
			for (; i <= min; ++i) {
				(current->child->at(i))->parent = first;
				first->child->push_back(current->child->at(i));
			}
			for (; i < current->child->size(); ++i){
				(current->child->at(i))->parent = second;
				second->child->push_back(current->child->at(i));
			}
		}
		delete current;
		current = parent;
	}//while;

	if (head->key->size()>m)//当处理到根结点时需要再创建一个新的根结点;
	{
		Node* first = new Node;
		Node*second = new Node;
		Node*newhead = new Node;
		first->key->assign((head->key)->begin(), (head->key)->begin() + min+1 );
		first->child->assign((head->child)->begin(), (head->child)->begin() + min+1);
		second->key->assign((head->key)->begin() + min+1, (head->key)->end());
		second->child->assign((head->child)->begin() + min+1, (head->child)->end());
		first->parent = newhead;
		first->next = second;
		second->parent = newhead;
		second->pre = first;
		newhead->key->push_back(*((head->key)->begin() + min ));
		newhead->key->push_back(*((head->key)->end() - 1));
		newhead->child->push_back(first);
		newhead->child->push_back(second);
		if (head->child->size() != 0)//如果当前结点有孩子结点;
		{
			//	问题出在了创建新的结点代替满结点
			//	将孩子指针指向新的父亲结点
			int i = 0;
			for (; i <= min; ++i) {
				head->child->at(i)->parent = first;
				
			}
			for (; i < current->child->size(); ++i) {
				head->child->at(i)->parent = second;

			}
		}
		delete head;
		head = newhead;
	}
}
void bPlus::changeSmall(Node* node) {//删除一个结点的最大值后，修改其父亲结点对应的最大值;
	if (node->parent!=NULL)
	{
		int i = 0;
		while (node->parent->child->at(i) != node)
			i++;
		node->parent->key->at(i) = node->key->back();
		if (i == node->parent->key->size() - 1)
		{
			changeSmall(node->parent);
		}
	}
}

void bPlus::deletekey(int key) {
	Node* deleteNode = search(key);
	vector<int>::iterator ve = deleteNode->key->begin();
	for (; ve < deleteNode->key->end(); ve++) {
		if (*ve == key)
			break;
	}
	deleteNode->key->erase(ve);
	if (deleteNode->key->size() >= min)//如果要删除关键字的结点个数大于要求最小值;
	{
		if (key > deleteNode->key->back())
		{
			changeSmall(deleteNode);
		}
	}//if;

	else//如果删除后个数小于min时;
	{
		if (key > deleteNode->key->back())
			changeSmall(deleteNode);
		Node* brother=NULL;
		//接下来我只是考虑结点个数大于 1 个时的情况;
		if (deleteNode == deleteNode->parent->child->back())//如果是最后一个孩子，则兄弟结点是前一个孩子;
		{
			brother = deleteNode->pre;
		}
		else 
		{
			brother = deleteNode->next;
		}

		if (brother->key->size()>min)//		1. 如果可以向兄弟结点借用;
		{
				BrrowKey(deleteNode, brother);
		}
		else//2.兄弟结点元素个数也不够的话就可以合并啦
		{
			if(deleteNode->pre==brother)//是上兄弟;
			{
				leavesUnion(brother, deleteNode);
				if (brother->parent->key->size()<min)//小于min了，应该怎么办！！写呗;
				{
						Union(brother->parent);
				}
			}
			else//是下兄弟;
			{
				leavesUnion(deleteNode, brother);
				if (deleteNode->parent->key->size()<min)//小于min了，应该怎么办！！写呗;
				{
						Union(deleteNode->parent);					
				}
			}//else;
		}//else;
	}
}
void bPlus::BrrowKey(Node* deleteNode, Node* brother) {
	if (deleteNode->next==brother)//if the brother is next of deleteNode;
	{
		deleteNode->key->push_back(brother->key->front());
		brother->key->erase(brother->key->begin());
		if (brother->child->size()>0)//;
		{
			deleteNode->child->push_back(brother->child->front());
			brother->child->erase(brother->child->begin());
			deleteNode->child->back()->parent = deleteNode;
		}
		changeSmall(deleteNode);
	}
	else
	{
		deleteNode->key->insert(deleteNode->key->begin(), brother->key->back());			
		brother->key->pop_back();// PAY ATITION;
		if (deleteNode->child->size()>0)
		{
			deleteNode->child->insert(deleteNode->child->begin(), brother->child->back());
			brother->child->pop_back();
			deleteNode->child->front()->parent = deleteNode;
		}
		changeSmall(brother);
	}
}
Node*  bPlus::search(int key) {
	Node* current = head;
	while (current->child->size()!=0)//只要没有孩子结点了就是叶子结点;
	{
		if (key>current->key->back())
		{
			current = current->child->back();
		}
		else
		{
			for (int position = 0; position < current->key->size(); position++)
				if (current->key->at(position) >= key)
				{
					current = current->child->at(position);
					break;
				}
		}
		//if (position== current->key->size())
		//{
		//	current = current->child->back();
		//}
	}//while;
	return current;//将查找到的要插入的叶子结点返回;
}

void bPlus::Union(Node* node) {          //问题
	//找到 node 结点的兄弟结点合并;
	if ((node->parent) == NULL)
	{
		for (int i = 0; i < node->key->size(); i++)
			node->child->at(i)->parent = NULL;
		
		head = head->child->at(0);
		delete node;
		return;
	}
	Node* brother;
	if (node->parent->child->back()==node)//;
	{
		brother = node->pre;
		//也要先考虑先借再合并;
		if (brother->key->size()>min)
		{
			BrrowKey(node, brother);
		}
		else
		{
			brother->key->insert(brother->key->end(), node->key->begin(), node->key->end());
			brother->child->insert(brother->child->end(), node->child->begin(), node->child->end());
			brother->next = node->next;
			if (node->next != NULL)
				node->next->pre = brother;
			for (int i = 0; i < node->key->size(); ++i)
				node->child->at(i)->parent = brother;
			delete node;
			node = NULL;
			vector<int>::iterator itKey = brother->parent->key->begin();
			vector<Node*>::iterator itChild = brother->parent->child->begin();
			int i = 0;
			while (brother->parent->child->at(i) != brother) {
				i++;
				itKey++;
				itChild++;
			}
			*itKey = brother->key->back();
			//brother->parent->key->at(i) = brother->key->back();
			brother->parent->key->erase(++itKey);
			brother->parent->child->erase(++itChild);
		if (brother->parent->key->size()<min)
			Union(brother->parent);
		}
	}
	else
	{
		brother = node->next;
		if (brother->key->size()>min)
		{
			BrrowKey(node, brother);
		}
		else
		{
			node->key->insert(node->key->end(), brother->key->begin(), brother->key->end());
			node->child->insert(node->child->end(), brother->child->begin(), brother->child->end());
			node->next = brother->next;
			if (brother->next!=NULL)
			{
				brother->next->pre = node;
			}
			for (int i = 0; i < brother->key->size(); i++)
				brother->child->at(i)->parent = node;
			delete brother;
			brother = NULL;
			vector<int>::iterator itKey = node->parent->key->begin();
			vector<Node*>::iterator itChild = node->parent->child->begin();
			while (*itChild != node) {
				itChild++;
				itKey++;
			}
			*(itKey) = node->key->back();
			node->parent->key->erase(++itKey);
			node->parent->child->erase(++itChild);
			if (node->parent->key->size() < min)
				Union(node->parent);
		}//else
	}
}

void bPlus::leavesUnion(Node* left, Node* right) {
	//将右结点合并到左结点
	left->key->insert(left->key->end(), right->key->begin(), right->key->end());
	left->next = right->next;
	if (right->next!=NULL)
	{
		right->next->pre = left;
	}
	int i = 0;
	while (left->parent->child->at(i) != right)
		i++;
	left->parent->key->at(i-1) = left->key->back();
	left->parent->key->erase(left->parent->key->begin() + i  );
	left->parent->child->erase(left->parent->child->begin() + i );
	delete right;
	right = NULL;
}
bPlus::bPlus()
{
	InitBplus();
}


bPlus::~bPlus()
{
}
