#include <iostream>
#include "Graph.h"
#include <time.h>
#include <fstream>
#include <io.h>
#include<vector>
using namespace std;
int main(){

// 	ifstream re;
// 	re.open("E:\\Share\\Sort_data\\1.txt");
// 	if (re.bad())
// 	{
// 		cout<<123<<endl;
// 	}
// 	int tem;
// 	vector<int> ve;
// 
// 	while(!re.eof()){
// 		re>>tem;
// 		cout<<tem<<endl;
// 
// 	}
// 	re.close();

//	Graph te;
//	te.read();

	//cout<<"over"<<endl;

// 	char buf[1024];
// 	memset(buf,0,1024);
// 	string a;
// 	FILE *stream;
// 	//stream=fopen("E:/uniprot150m.txt","r");
// 	fopen_s(&stream,"E:/uniprot150m.txt","r");
// 	if(!fopen_s(&stream,"E:/uniprot150m.txt","r")){
// 		setvbuf( stream, buf, _IOFBF, sizeof( buf ) );
// 		getline(buf,a);
// 		//a=buf;
// 		cout<<a<<endl;
// 	}


	//string test1;
// 	char test1[8];
// 	memset(test1,0,sizeof(test1));
// 	cout<<"start"<<endl;
// 	ifstream fin ("E:/xmark.txt",ios::binary);
// 	fin.read(test1,sizeof(test1));
	//_read(fin,test1,sizeof(test1));

// 	int count=0;
// 	while(!fin.eof()){
// 		count++;
// 	}
// 	for (int i=0;i<sizeof(test1);++i)
// 	{
// 		cout<<test1[i];
// 	}
// 	cout<<endl;
// 	

// 
  	Graph test;
	clock_t time=clock();
	//test.creat_Linklist_Nodirection();
	//time=clock()-time;
	//cout<<"use time : "<<time<<endl;
	test.creat_Linklist_Direction();
	//time=clock()-time;
	//cout<<"use time : "<<time<<endl;
// 	cout<<"BFS_queue: "<<endl;
// 	test.BFS();
//  	cout<<endl;
// 	for(int i=0;i<test.vex_num;++i){
// 		test.head[i].statu=false;
// 	}

	cout<<"BFS_self: "<<endl;
	test.BFS_self();
	cout<<endl;

// 	cout<<"DFS: "<<endl;
// 	test.DFS_self();
// 	cout<<"DFS·ÇµÝ¹é×Ô¶¨ÒåÕ»: "<<endl;

	for(int i=0;i<test.vex_num;++i){
		test.head[i].statu=false;
	}
	cout<<"DFS_digui: "<<endl;
	test.DFS_digui();
// 	cout<<"DFS: "<<endl;
// 	test.DFS();
// 	cout<<"DFS·ÇµÝ¹éSTLÕ»: "<<endl;

	///²âÊÔ»º³åÇø;

	// 	ifstream in("E:/xmark.txt");
	// 	string  s;
	// 	getline(in,s);
	// 	int test;
	// 	istringstream iss(s);
	// 	iss >> test;
	// 	cout<<test<<endl;
	// 	
	// 	getline(in,s);
	// 	int pos=s.find(" ",0);
	// 	int start,end;
	// 	istringstream st(s.substr(0,pos));
	// 	st>>start;
	// 	cout<<start<<endl;
	// 	istringstream stt(s.substr(pos,s.length()));
	// 	stt>>end;
	// 	cout<<end<<endl;

	//	in.close();
	system("pause");
	return 0;
}