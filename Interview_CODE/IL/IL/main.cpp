#include "Read.h"
#include "IL.h"
#include <Windows.h>
void main(){
	clock_t start;
	int totle=0;
	CString str[32][7] = {  
		
		//{"2","text","keyword"},
		//{"2","keyword","text"},
			{"2","villages","hooks"},                            //11111111  1
			{"3","baboon","patients","arizona"},                //            2
		{"4","cabbage","tissue","shocks","baboon"},          //            3
		{"5","shocks","necklace","cognition","cabbage","tissue"},   //            4

		{"2","female","order"},                            //22222222    5
		{"3","privacy","check","male"},                      //            6
		{"4","takano","province","school","gender"},            //            7
		{"5","school","gender","education","takano","province"},  //            8

		{"2","bold","increase"},                           //33333333    9
		{"3","date","listitem","emph"},                       //            10
		{"4","incategory","text","bidder","date"},            //            11
		{"5","bidder","date","keyword","incategory","text"},    //            12

		{"2","text","tissue"},      //1,3                                13
		{"2","takano","province"},   //2,2                                14
		{"2","incategory","cabbage"}, //1,3                            15
		{"2","check","bidder"},       //2,3                            16
		{"2","baboon","patients"},   //1,1                            17

		{"3","tissue","shocks","order"},        //1,1,2                    18
		{"3","province","bold","increase"},        //233                    19
		{"3","cabbage","male","female"},         //122                    20
		{"3","listitem","emph","arizona"},        //133                    21
		{"3","patients","school","gender"},        //122                    22

		{"4","patients","school","gender","text"},        //1223            23
		{"4","bold","increase","hooks","takano"},            //1233            24
		{"4","male","female","keyword","incategory"},        //2233            25
		{"4","emph","arizona","villages","education"},    //1123            26
		{"4","check","bidder","date","baboon"},           //1233            27

		{"5","school","gender","time","baboon","patients"},             //11223    28
		{"5","tissue","shocks","order","province","bold"},           //11223    29
		{"5","female","keyword","incategory","cabbage","male"},         //12233    30
		{"5","arizona","villages","education","listitem","emph"},   //11233    31
		{"5","bidder","date","necklace","cognition","check"}       //11233    32

		/*
		{"2","article","book"},                            //11111111  1
		{"2","article","algorithm"},                //            2
		{"2","article","data"},            //            3
		{"2","article","database"},//            4
		{"2","article","xml"},  //22222222    5

		{"2","year","2001"}, //            6
		{"3","article","book","mining"},                //            7     
		{"3","article","algorithm","2001"},            //            8
		{"3","article","data","mining"},//33333333    9
		{"3","article","data","xml"}, //            10 


		{"2","article","book"},                            //11111111  1
		{"2","article","algorithm"},                //            2
		{"2","article","data"},            //            3
		{"2","article","database"},//            4
		{"2","article","xml"},  //22222222    5

		{"2","year","2001"}, //            6
		{"3","article","book","mining"},                //            7     
		{"3","article","algorithm","2001"},            //            8
		{"3","article","data","mining"},//33333333    9
		{"3","article","data","xml"} ,//      10


		{"2","article","book"},                            //11111111  1
		{"2","article","algorithm"},                //            2
		{"2","article","data"},            //            3
		{"2","article","database"},//            4
		{"2","article","xml"},  //22222222    5

		{"2","year","2001"}, //            6
		{"3","article","book","mining"},                //            7     
		{"3","article","algorithm","2001"},            //            8
		{"3","article","data","mining"},//33333333    9
		{"3","article","data","xml"}, //      10

		{"2","article","book"},                            //11111111  1
		{"2","article","algorithm"},                //            2
// 		{"2","article","data"},            //            3
// 		{"2","article","database"},//            4
// 		{"2","article","xml"},  //22222222    5
// 
//  		{"2","year","2001"}, //            6
//  		{"3","article","book","mining"},                //            7     
//  		{"3","article","algorithm","2001"},            //            8
//  		{"3","article","data","mining"},//33333333    9
//  		{"3","article","data","xml"} 
		*/

	};
	IL il;
	int num=0;
	
	for (int j=0;j<32;j++)
	{
		//il.input();////////////////////
		il.testdata(str,num);
		DWORD time=GetTickCount();
		//tem=il.get_slca(il.S[0],il.S[1]);
 		for (int i=1;i<il.n;++i)
 		{
 			il.S[0]=il.get_slca(il.S[0],il.S[i]);
 		}
		time=GetTickCount()-time;
		cout<<"时间："<<time<<"ms"<<endl;
		totle=totle+time;
 		cout<<"返回结果个数： "<<il.S[0]->GetSize()<<endl;
		cout<<"*************************************"<<endl;
		num++;
	}
	cout<<"总时间为："<<totle<<endl;
	system("pause");
}