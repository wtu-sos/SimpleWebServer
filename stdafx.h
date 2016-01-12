//
//		预定义文件头
//

#ifndef _STD_AFX_H
#define _STD_AFX_H

#include<iostream>
#include<sstream>
#include<string>
#include<vector>

using namespace std;

enum eCommandType {
	eGet,
	ePost,
	eHead,

	eUnknow,
};

struct cmd_data{
	eCommandType	eType;
	string			param;

	cmd_data(vector<string> dt) {
		if (dt.empty())
		{
			eType = eUnknow;
			return;
		}

		if (dt[0] == "GET")
		{
			eType = eGet;
			param = dt[1];
		}
	}
};

#endif 
