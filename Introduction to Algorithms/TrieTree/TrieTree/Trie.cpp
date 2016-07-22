#include "Trie.h"
node* Trie::MakeTrie() {
	node* t = new node;
	return t;
}

node* Trie::search(node* T, const char* a) {
	int i = 0;
	node* temp = T;

	while (a[i]!='\0')
	{
		 if((temp->child)[a[i]-'a']!=NULL)
		{
			temp = (temp->child)[a[i] - 'a'];
			i++;
		}else
		{
			cout << "Not find the words" << endl;
			return NULL;
		}
	}//while	;
	if (temp->mark)
	{
		//cout << "have the words! " << endl;
		return temp;
	}
	else
	{
		cout << "Not find the words" << endl;
		return NULL;
	}
}

void Trie::Delete(node* T,const char* a) {
	int i = 0;
	node* temp = T;
	temp = search(T, a);
	if (temp==NULL)
	{

	}
	else {
		temp->mark = false;
		//cout << "Delete success ! " << endl;
	}

}

void Trie::Insert(node*T,const char* a) {
	int i = 0;
	node* temp=T;
	while (a[i]!='\0')
	{
		if ((temp->child)[a[i]-'a']!=NULL)//如果已经存在本字母;
		{
			(temp->num)++;
			temp = (temp->child)[a[i] - 'a'];
			//temp->alphabet = a[i];
			//temp = (temp->child)[a[i] - 'a'];
		}
		else//还没有当前字母;
		{
			node* newnode = new node;
			newnode->alphabet = a[i];
			(temp->child)[a[i] - 'a'] = newnode;
			temp = newnode;
			(temp->num)++;
		}
		i++;
	}
	temp->mark = true;//添加完成;
}

Trie::Trie()
{
}


Trie::~Trie()
{
}
