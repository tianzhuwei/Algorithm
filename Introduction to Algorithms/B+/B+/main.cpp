#include"bPlus.h"
#include<time.h>
#include<fstream>
int main() {
	int po = 0;
	vector<int> ve;
	fstream readfile("E:\\B+\\mid.txt");
	while (!readfile.eof())
	{
		readfile >> po;
		ve.push_back(po);
	}
	bPlus test;
	clock_t time = clock();
	readfile.close();
	for (int i = 0; i < ve.size(); ++i)
	{
		test.addKey(i);
		//cout << "insert success " << i << endl;
	}
	time = clock() - time;
	cout << "创建完成！use time  " << time << "ms" << endl;
	//Node* s = test.search(1);
	//while (s!=NULL)
	//{
	//	vector<int>::iterator it = s->key->begin();
	//	for (; it < s->key->end(); ++it)
	//		cout << *it << " ";
	//	s = s->next;
	//}
	cout << endl;
	cout << "测试删除： " << endl;
	time = clock();
	for(int i=0;i<ve.size()-10;i++){
		test.deletekey(ve[i]);
		//cout << "删除 " << ve[i] << " 成功！" << endl;
	}

	//for (int i = 999; i >10; i--)
	//{
	//	test.deletekey(i);
	//	cout << "删除 " << i << " 成功！" << endl;
	//}
	cout << "time " << time <<"ms" << endl;
	system("pause");
	return 0;
}