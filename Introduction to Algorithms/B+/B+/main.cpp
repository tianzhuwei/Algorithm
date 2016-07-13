#include"bPlus.h"
int main() {
	bPlus test;
	for (int i = 0; i <10000; ++i)
	{
		test.addKey(i);
		//cout << "insert success " << i << endl;
	}
	cout << "创建完成！ " << endl;
	Node* s = test.search(1);
	//while (s!=NULL)
	//{
	//	vector<int>::iterator it = s->key->begin();
	//	for (; it < s->key->end(); ++it)
	//		cout << *it << " ";
	//	s = s->next;
	//}
	cout << endl;
	cout << "测试删除： " << endl;
	cout << endl;
	for (int i = 199; i >35; i--)
	{
		test.deletekey(i);
		cout << "删除 " << i << " 成功！" << endl;
	}
	system("pause");
	return 0;
}