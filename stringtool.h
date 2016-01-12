/*
	stringtool.h
*/

#ifndef _STRING_TOOL_
#define _STRING_TOOL_

#include "stdafx.h"

class stringtool {
public:
	static void splite(const std::string& str, const std::string& sign, std::vector<std::string>& svec);
	static string Get404Respond();
};

#endif 
