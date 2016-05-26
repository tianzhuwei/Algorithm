#include "Read.h"

Read::Read(void)
{
	CFile destFile;//文件打开对象;
	CFileException ex;//错误信息收集;
	mycmap.InitHashTable(41);//对CMAP进行初始化;

	CString strProcessed, strWordLabel, strKeyword, strLabel,strListLength,strFirst,strComp;
	int i,nPos,nStart,nEnd,nListLength,nListLenIter,nStartIn,nEndIn,nSize,nComp;
	int count=0;
	int * pLabel;

	CArray<int *, int *> * pDFDeweyList;

	CString strFile="F:\\weitianzhu\\个人\\IL\\data\\dblp.txt";
	//CString strFile="C:\\Users\\weitianzhu\\Desktop\\IL\\data\\xmark5.txt";
	//CString strFile="C:\\Users\\weitianzhu\\Desktop\\IL\\data\\dblp.txt";
	//CString strFile="C:\\Users\\weitianzhu\\Desktop\\IL\\data\\dblp2.txt";
	
	//CString strFile="F:\\IndexTxt\\xmark5.txt";
	//CString strFile="D://xmark500.txt";6
	if (!destFile.Open(((LPCTSTR)strFile),CFile::modeRead,&ex)){//如果不能打开则输出错误信息;
		TCHAR szError[1024];
		ex.GetErrorMessage(szError, 1024);
		cout << "Couldn't open source file: ";
		cout << szError;
		return;
	}

	//将关键字进行保存操作;
	while(1) //each time read a keyword and all its labels
	{
		if(strProcessed.Find('>') == -1)	//找不到 '>' 的话，执行该语句;
		{
			if(!SetBuffer(strProcessed, 1024, destFile))//在打开文件流后，读取内容之前，调用setbuffer（）可用来设置文件流的缓冲区。
				////参数strProcessed为指定的文件流,参数BUFFERSIZE为缓冲区大小,参数destFile指向自定的缓冲区起始地址。
			{
				break;
			}
		}

		nPos = strProcessed.Find('>');//返回'>'的索引，第一个字符的索引为0;
		strWordLabel = strProcessed.Left(nPos);//取出数据流左边npos个字符;
		strProcessed = strProcessed.Mid(nPos+1);//取出数据流从第npos开始的字符;
		strProcessed.Trim();//删除空格;

		//去掉<>;
		strWordLabel.TrimLeft('<');//从左边开始删掉<，直到不匹配;
		strWordLabel.TrimRight('>');//从右边开始删除>，直到不匹配;

		//取出关键字;
		nStart = 0;
		nEnd = strWordLabel.Find(':');//第一个：的索引（：前是关键字）;
		strKeyword = strWordLabel.Mid(nStart, nEnd-nStart);//Left(nPos);将关键字赋给strKeyword 
		mycmap.operator[](strKeyword);//将关键字保存入CMap;
		cout<<++count;
		wcout<<(LPCTSTR)strKeyword<<endl;

		//取出关键字的个数,设置CArray的长度（= 关键字的个数）;
		nStart = nEnd + 1;

		nEnd = strWordLabel.Find(':', nStart);//第二个：的索引（：前是此关键字对应的编码个数）;
		strListLength = strWordLabel.Mid(nStart, nEnd-nStart);//Left(nPos); //list length将编码个数赋给strListLength
		nStart = nEnd + 1;

		nListLength = _ttoi(strListLength);//字符串转换成整型数,即将关键字的编码个数转化为整型;

		if(mycmap.Lookup(strKeyword, pDFDeweyList))//在哈希表中查找关键字，若存在，存入pDFDeweyList
		{
			pDFDeweyList = new CArray<int *, int *>;
			pDFDeweyList->SetSize(nListLength);//建立指针数组，长度为nListLength
			mycmap[strKeyword] = pDFDeweyList;
		}
		else
		{
			cout << "error" << endl;
		}

		//处理编码;
		nListLenIter = 0;

		//read all its labels
		while(nStart < strWordLabel.GetLength() )//返回strWordLabel的字节个数，即第一个关键字的全部编码
		{
			//取出一个编码;
			nEnd = strWordLabel.Find(';', nStart);
			strLabel = strWordLabel.Mid(nStart, nEnd-nStart);//Left(nPos);取出第一段编码
			nStart = nEnd + 1;//用于循环;

			//construct the hash mapping between each id and the corresponding label

			//the first number
			nStartIn = 0;
			nEndIn = strLabel.Find('.');
			strFirst = strLabel.Mid(nStartIn, nEndIn-nStartIn);//Left(nPos);取出第一小段编码的数字个数
			nStartIn = nEndIn + 1;

			//nSize等于编码长度
			nSize = _ttoi(strFirst); //notice the first label: site.1.1, which should be processed specially将第一段编码的数字个数转为整型
			pLabel = new int[nSize+1];//开辟内存
			(*pDFDeweyList)[nListLenIter] = pLabel;//nListLenIter为*pDFDeweyList的索引
			nListLenIter ++;

			i = 0;
			pLabel[i] = nSize;//第0个位置存储编码的长度
			i ++;

			//依次取出一个结点的编码;
			while(nStartIn < strLabel.GetLength())//读取第一小段编码;
			{
				if(strLabel.Find('.', nStartIn) == -1)
				{
					nComp = _ttoi(strLabel.Mid(nStartIn));//从编码的第一个数字开始转为整型;
					pLabel[i] = nComp;//依次存储数字个数;
					i++;
					nStartIn = strLabel.GetLength();
				}
				else
				{
					nEndIn = strLabel.Find('.', nStartIn);
					strComp = strLabel.Mid(nStartIn, nEndIn-nStartIn);//Left(nPos);
					nStartIn = nEndIn + 1;

					nComp = _ttoi(strComp);

					pLabel[i] = nComp;
					i++;
				}
			}

			ASSERT(i == nSize+1);

			//construct the hash mapping between each keyword and its DFDewey label list
		}


	}//while;
	destFile.Close();
}//end;

Read::~Read(void){

}

BOOL Read::SetBuffer(CString& strBuf, int nBreakPos, CFile& destFile){//设置文件流的缓冲区大小;
					 //（起始地址，缓冲区大小，指定的文件流）;
	char pbuf[1024]={0};			//256K each time
	CString strTail;
	long nRead = 0;
	CString strTemp;

	memset(pbuf, 0, 1024);//将pbuf中前BUFFERSIZE个字节置换为0

	nRead= destFile.Read(pbuf, 1024-1);  //从文件读出BUFFERSIZE-1个字符放入pbuf，返回实际读取到的字符，最多256K

	strTemp = pbuf;  //将读出的内容转化为CString类型

	strTemp = strBuf + strTemp;//什么意思？？？;

	strTemp.Trim();//清除空格;

	//to the end of the file
	if(strTemp.GetLength() == 0)
	{
		return FALSE;
	}

	//contains a keyword and all its labels or ids
	if(strTemp.Find('>') != -1)//若文件流中存在'>';
	{
		strBuf = strTemp;//将文件流赋给strBuf
		return TRUE;
	}
	else 
	{
		strBuf = strTemp;
		while(1)
		{
			memset(pbuf, 0, 1024);//作用是在一段内存块中填充某个给定的值，它是对较大的结构体或数组进行清零操作的一种最快方法;
			nRead= destFile.Read(pbuf, 1024-1);
			strTemp = pbuf;
			strBuf += strTemp;

			if(strTemp.Find('>') != -1)
			{
				return TRUE;
			}
		}
	}

	return TRUE;
}