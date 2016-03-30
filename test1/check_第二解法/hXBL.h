#pragma once
using namespace std;
#include <vector>

class hXBL
{
public:
	hXBL(void);
	~hXBL(void);
	static bool glob;
	void change(vector<int> a, int start,int end);
	bool result(vector<int> a);
};

