#include "stdafx.h"
#include "Socket.h"
#include "stringtool.h"
#include "command.h"

string process_cmd(const vector<string>& cmd);

int main ( int argc, char* argv[] )
{
	std::cout << "running....\n";
	Socket server(30000);

	while (true)
	{
		Socket new_sock;

		while (server.accept(new_sock))
		{
			std::string data;
			new_sock.recv(data);
			std::vector<std::string> cmd;
			size_t idx = data.find("\r\n");
			data = data.substr(0, idx);
			stringtool::splite(data, " ", cmd);
			std::cout << data << std::endl;
			
			string strRespond;
			strRespond = process_cmd(cmd);
			new_sock.send(strRespond);
			cout << strRespond << endl;
		}

	}

	return 0;
}

string process_cmd(const vector<string>& cmd)
{
	command* pCmd = CommandFactory::Instant()->create(cmd[0], cmd[1]);
	if (NULL == pCmd)
		return  stringtool::Get404Respond();

	return pCmd->doCommand();
}
