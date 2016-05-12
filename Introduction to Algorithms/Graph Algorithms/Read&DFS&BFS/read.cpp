void Graph::readfile(){
	clock_t time=clock();
	//ifstream my("E:/xmark.txt");
	ifstream my("E:/uniprot150m.txt");
	//ifstream my("E:/test.txt");

//方法一
	my>>vexNum;
	int f1,f2;
	while (!my.eof())
	{
		my>>f1>>f2;
		if(my.fail())
		{
			break;
		}
		//cout<<f1<<" "<<f2<<endl;
	}
	time=clock()-time;
	cout<<"success! use time :"<<time<<endl;
	my.close();

//方法二
	if (my)
	{
		clock_t time=clock();
		string t;
		my.seekg(0,my.end);
		int length=my.tellg();
		my.seekg(0,my.beg);
		char * buffer =new char[length];
		//memset(buffer,0,length*sizeof(char));
		memset(buffer,0,length);
		cout<<"reading "<<length<<endl;
		my.read(buffer,length);
		//sprintf(buffer,buffer+'\n');
		if (my)
		{
			t=buffer;
			//cout<<"success"<<endl;
		}else{
			t=buffer;
		//	cout<<"fail!"<<endl;
		}

		int pos1=0,pos2=0;
	
		pos2=t.find("\n",0);
		istringstream vv(t.substr(pos1,pos2));
		vv>>vexNum;
		cout<<"number of vex "<<vexNum<<endl;
		initArcNode();
		string start,end;
		int s,e;
		while(t.find("\n",pos2)!=-1){
			pos1=t.find(" ",pos2++);
			start=t.substr(pos2,pos1-pos2);
			//cout<<start<<endl;
			pos2=t.find("\n",pos2);
			end=t.substr(++pos1,pos2-pos1);
			//cout<<end<<endl;
			//cout<<start<<" "<<end<<" ";
			istringstream ss(start);
			ss>>s;
			istringstream ee(end);
			ee>>e;
			dirGraph(s,e);
		}
		time=clock()-time;
		cout<<" use time "<<time<<endl;
	}
}