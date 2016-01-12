#include "stringtool.h"

void stringtool::splite(const std::string& str, const std::string& sign,  std::vector<std::string>& svec) 
{
	std::string data(str); 
	size_t idx = 0;
	while ((idx = data.find(sign)) != std::string::npos)
	{
		std::string temp = data.substr(0, idx);
		data.erase(0,idx+1);

		std::stringstream oss;
		oss << temp;
		string result;
		oss >> result;
		svec.push_back(result);
	}

}

string stringtool::Get404Respond() {
	static string strRespond("HTTP/1.1 404 Not Found\r\nContent-type: text/plain\r\n\r\n");
	return strRespond;
}

