#include "hXBL.h"


bool hXBL::glob =true ;

hXBL::hXBL(void)
{
}


hXBL::~hXBL(void)
{
}
void hXBL::change(vector<int> a, int start,int end){

	if (start<end)
	{
		int tem=end-1;
		while(a[end]<a[tem]&&tem>=0){
			tem--;
		}
		while(tem>=0){
			if (a[end]<a[tem])
			{
				glob=false;
				return;
			}
			tem--;
		}
		change(a,start,tem);
		change(a,tem+1,end-1);
	}

}
bool hXBL::result(vector<int> a){
	//int start=a.begin();
	int end=a.size()-1;
	change(a,0,end);
	return glob;

}