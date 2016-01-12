#include "command.h"
#include "stringtool.h"
#include <sys/stat.h>

GetCommand::GetCommand(const cmd_data& _data): data(_data) {
}

string GetCommand::doCommand() {
	struct stat info;
	if (stat(data.param.c_str(), &info) != -1 && S_ISDIR(info.st_mode))	
		return stringtool::Get404Respond();
	
	return stringtool::Get404Respond();
}
