#pragma once
#include <afxtempl.h>
#include <iostream>
#include "Node.h"
using namespace std;

class Read
{
public:
	CMap<CString,LPCTSTR, CArray<int*,int*>*,CArray<int*,int*>*> mycmap;

public:
	Read(void);
	BOOL SetBuffer(CString& strBuf, int nBreakPos, CFile& destFile);
	~Read(void);
};