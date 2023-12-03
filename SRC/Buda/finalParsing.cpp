#include "../../includes/Webserv.hpp"


Parsing::Parsing()
{
	httpStatusCodes.push_back("100");
	httpStatusCodes.push_back("101");
	httpStatusCodes.push_back("102");

	// 2xx (Successful)
	httpStatusCodes.push_back("200");
	httpStatusCodes.push_back("201");
	httpStatusCodes.push_back("202");
	httpStatusCodes.push_back("203");
	httpStatusCodes.push_back("204");
	httpStatusCodes.push_back("205");
	httpStatusCodes.push_back("206");
	httpStatusCodes.push_back("207");
	httpStatusCodes.push_back("208");
	httpStatusCodes.push_back("226");

	// 3xx (Redirection)
	httpStatusCodes.push_back("300");
	httpStatusCodes.push_back("301");
	httpStatusCodes.push_back("302");
	httpStatusCodes.push_back("303");
	httpStatusCodes.push_back("304");
	httpStatusCodes.push_back("305");
	httpStatusCodes.push_back("307");
	httpStatusCodes.push_back("308");

	// 4xx (Client Errors)
	httpStatusCodes.push_back("400");
	httpStatusCodes.push_back("401");
	httpStatusCodes.push_back("402");
	httpStatusCodes.push_back("403");
	httpStatusCodes.push_back("404");
	httpStatusCodes.push_back("405");
	httpStatusCodes.push_back("406");
	httpStatusCodes.push_back("407");
	httpStatusCodes.push_back("408");
	httpStatusCodes.push_back("409");
	httpStatusCodes.push_back("410");
	httpStatusCodes.push_back("411");
	httpStatusCodes.push_back("412");
	httpStatusCodes.push_back("413");
	httpStatusCodes.push_back("414");
	httpStatusCodes.push_back("415");
	httpStatusCodes.push_back("416");
	httpStatusCodes.push_back("417");
	httpStatusCodes.push_back("418");
	httpStatusCodes.push_back("421");
	httpStatusCodes.push_back("422");
	httpStatusCodes.push_back("423");
	httpStatusCodes.push_back("424");
	httpStatusCodes.push_back("426");
	httpStatusCodes.push_back("428");
	httpStatusCodes.push_back("429");
	httpStatusCodes.push_back("431");
	httpStatusCodes.push_back("451");

	// 5xx (Server Errors)
	httpStatusCodes.push_back("500");
	httpStatusCodes.push_back("501");
	httpStatusCodes.push_back("502");
	httpStatusCodes.push_back("503");
	httpStatusCodes.push_back("504");
	httpStatusCodes.push_back("505");
	httpStatusCodes.push_back("506");
	httpStatusCodes.push_back("507");
	httpStatusCodes.push_back("508");
	httpStatusCodes.push_back("510");
	httpStatusCodes.push_back("511");
}

std::vector<std::string> Parsing::getHttpStatusCodes()
{
	return httpStatusCodes;
}

bool checkListen(std::string &data)
{
	size_t i = data.find(':');
	if (i == std::string::npos)
	{
		if (isValidPort(data))
			return true;
		return false;
	}
	if (!isValidIPAddress(data.substr(0, i)) || !isValidPort(data.substr(i + 1)))
		return false;
	return true;
}

bool checkServerData(std::vector<std::string> &data)
{
	if (data[0] == "methods" && (data.size() < 2 || !isValidLocationMethods(data)))
		return false;
	if (data[0] == "listen" && (data.size() != 2 || !checkListen(data[1])))
		return false;
	if (data[0] == "autoindex" && (data.size() != 2 || !isValidAutoIndex(data[1])))
		return false;
	if (data[0] == "upload_dir" && (data.size() != 2 || !isValidUploadDir(data[1])))
		return false;
	if (data[0] == "root" && (data.size() != 2 || !isValidRoot(data[1])))
		return false;
	if (data[0] == "client_body_max_size" && (data.size() != 2 || !isValidClientBodyMaxSize(data[1])))
		return false;
	if (data[0] == "error_page" && (data.size() != 3 || !isValidErrorPage(data[1])))
		return false;
	if (data[0] == "cgi" && (data.size() != 3 || !isValidLocationCGI(data[1], data[2])))
		return false;
	if (data[0] == "server_name" && data.size() != 2)
		return false;
	if (data[0] == "redirect" && (data.size() != 3 || !isValidErrorPage(data[1])))
		return false;
	if (data[0] == "index" && data.size() != 2)
		return false;
	return true;
}

bool isValideServerCp(serverConfigData &data)
{
	if (data.listen  != 1 || data.root != 1 || data.client_body_max_size != 1 || data.redirect > 1 || data.index > 1 || data.autoindex > 1 || data.upload_dir > 1)
		return false;
	return true;
}
bool isValideLocationCp(locationConfigData &data)
{
	if (data.listen != 0 || data.root != 1 || data.client_body_max_size != 1 || data.mathods != 1 || data.redirect > 1 || data.index > 1 || data.autoindex > 1 || data.upload_dir > 1)
		return false;
	return true;
}

bool Parsing::checkRepetedServers()
{
	std::map < std::string, std::string >  serverPort;


	for (size_t i = 0; i < servers.size(); i++)
	{
		std::string port = getServerDataSingle(i + 1, "listen");
		std::string key = ft_split(port, ':' )[1];
		std::string val = getServerDataSingle(i + 1, "server_name");
		std::cout << "key: " + key + "\t\t" + "val: " + val   << std::endl;
		std::map < std::string, std::string >::iterator it = serverPort.find(key);
		if (it != serverPort.end() && it->second == val)
			return false;
		serverPort[key] = val;
	}

	for (std::map  < std::string, std::string >::iterator i = serverPort.begin();
	i != serverPort.end(); i++)
	{
		std::cout << "listen: " + i->first << "\t\t\t" << "server_name: "+ i->second << std::endl;
	}
	
	return true;
}

bool Parsing::finalConfigFileParsing()
{
	for (size_t i = 0; i < servers.size(); i++)
	{
		for (size_t j = 0; j < servers[i].size(); j++)
		{
			std::vector<std::string> line = ft_split(servers[i][j]);
			if (line[0] == "location" && line.size() != 2)
			{
				std::cout << "Error on " << "\033[0;31m" << servers[i][j] << "\033[0m" << std::endl;
				return false;
			}
			if (!checkServerData(line))
			{
				std::cout << "Error on " << "\033[0;31m" << servers[i][j] << "\033[0m" << std::endl;
				return line.clear(), false;
			}
			line.clear();
		}
	}
	serverConfigData serverCp;
	locationConfigData locationCp;
	for (size_t i = 0; i < servers.size(); i++)
	{
		memset(&serverCp, 0, sizeof(serverConfigData));
		for (size_t j = 0; j < servers[i].size(); j++)
		{
			std::vector<std::string> line = ft_split(servers[i][j]);
			if (line[0] == "listen")
				serverCp.listen++;
			if (line[0] == "root")
				serverCp.root++;
			if (line[0] == "client_body_max_size")
				serverCp.client_body_max_size++;
			if (line[0] == "redirect")
				serverCp.redirect++;
			if (line[0] == "index")
				serverCp.index++;
			if (line[0] == "autoindex")
				serverCp.autoindex++;
			if (line[0] == "upload_dir")
				serverCp.upload_dir++;

			if (line[0] == "location")
			{
				line.clear();
				memset(&locationCp, 0, sizeof(locationConfigData));
				j++;
				while (j < servers[i].size())
				{
					line = ft_split(servers[i][j]);
					if (line[0] == "listen")
						locationCp.listen++;
					if (line[0] == "root")
						locationCp.root++;
					if (line[0] == "client_body_max_size")
						locationCp.client_body_max_size++;
					if (line[0] == "methods")
						locationCp.mathods++;
					if (line[0] == "redirect")
						locationCp.redirect++;
					if (line[0] == "index")
						locationCp.index++;
					if (line[0] == "autoindex")
						locationCp.autoindex++;
					if (line[0] == "upload_dir")
						locationCp.upload_dir++;
					if (line[0] == "location" || line[0] == "_")
					{
						--j;
						break;
					}
					line.clear();
					j++;
				}
				if (!isValideLocationCp(locationCp))
				{
					std::cout << "Error in " << "\033[0;31m" << "the location config" << "\033[0m" << std::endl;
					return false;
				}
			}
			line.clear();
		}
		if (!isValideServerCp(serverCp))
		{
			std::cout << "Error in " << "\033[0;31m" << "the server config" << "\033[0m" << std::endl;
			return false;
		}
	}

	if (!checkRepetedServers())
		return false;

	return true;
}
