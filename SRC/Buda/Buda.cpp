#include "../../includes/Request.hpp"

bool Webserv::isValidPort(const std::string& port)
{
	std::istringstream ss(port);
	int portNumber;
	ss >> portNumber;
	return !ss.fail() && portNumber >= 0 && portNumber <= 65535;
}

bool Webserv::isValidIPAddress(const std::string& ipAddress)
{
	std::istringstream ss(ipAddress);
	std::string octet;
	std::vector<int> octets;

	while (std::getline(ss, octet, '.'))
	{
		int num = std::atoi(octet.c_str());
		if (num < 0 || num > 255) 
			return false; 
		if (octet.length() > 1 && octet[0] == '0') 
			return false;
		octets.push_back(num);
	}
	return (octets.size() == 4);
}

bool Webserv::isDirectory( const std::string& path)
{
	struct stat fileInfo;
	if (stat(path.c_str(), &fileInfo) != 0)
		return false;
	return S_ISDIR(fileInfo.st_mode);
}

bool Webserv::isFile( const std::string& path)
{
	struct stat fileInfo;
	if (stat(path.c_str(), &fileInfo) != 0)
		return false;
	return S_ISREG(fileInfo.st_mode);
}

bool Webserv::isValideAutoIndex(const std::string& autoindex)
{
	if (autoindex != "on" || autoindex != "off")
		return false;
	return true;
}

bool Webserv::isValideUploadDir(const std::string& uploadDir)
{
	return isDirectory(uploadDir);
}
bool Webserv::isValideRoot(const std::string& root)
{
	return isDirectory(root);
}

bool Webserv::isValideClientBodyMaxSize(const std::string& clientBodyMaxSize)
{
	//GMKB
	int cp = 0;
	std::string::const_reverse_iterator it = clientBodyMaxSize.rbegin();
	for (; it != clientBodyMaxSize.rend(); ++it) 
	{
		if (*it == 'G' || *it == 'M' || *it == 'K' || *it == 'B')
		{
			cp++;
			continue;
		}
		else
			break;
    }
	std::cout << cp << std::endl;
	return true;
}
