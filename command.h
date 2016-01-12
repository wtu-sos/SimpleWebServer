/*命令*/
#include<map>
#include "stdafx.h"
#include "singleleton.h"

class command {
public:
	virtual std::string doCommand() = 0;
	virtual void  setParam(const std::string& str) = 0;
	~command(){}
};


class GetCommand : public command {
public:
	GetCommand(const cmd_data& _cmd);
	virtual void  setParam(const std::string& str) {
		data.param = str;
	};
	virtual std::string doCommand();
	~GetCommand(){}
private:
	cmd_data data;
};

class CommandFactory : public Singleton<CommandFactory> {
public:
	command* create(const cmd_data& cmd) {
		if (NULL == commandMp[cmd.eType]) 
		{
			if (eGet == cmd.eType)
				commandMp[cmd.eType] = new GetCommand(cmd);
		}

		return commandMp[cmd.eType];
	}

	~CommandFactory()
	{
		typedef std::map<eCommandType, command*>::iterator cmdIter;
		for (cmdIter it = commandMp.begin(); it != commandMp.end(); ++it)
		{
			if (NULL != it->second)
			{
				delete it->second;
				it->second = NULL;
			}
		}
		commandMp.clear();
	}

private:
	std::map<eCommandType, command*> commandMp;	
};
//typedef  CommandFactoryInst;
