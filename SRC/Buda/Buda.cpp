#include "../../includes/Webserv.hpp"

bool isValidPort(const std::string& port)
{
	std::istringstream ss(port);
	int portNumber;
	ss >> portNumber;
	return (!ss.fail() && ss.eof() && portNumber >= 0 && portNumber <= 65535);
}

bool isValidIPAddress(const std::string& ipAddress)
{
	if (ipAddress == "127.0.0.1" || ipAddress == "localhost" || ipAddress == "0.0.0.0")
		return true;
	return false;
}

bool isDirectory(const std::string& path)
{
	struct stat fileInfo;
	if (stat(path.c_str(), &fileInfo) != 0)
		return false;
	return S_ISDIR(fileInfo.st_mode);
}

bool isFile(const std::string& path, bool permission)
{
	struct stat fileInfo;
	if (stat(path.c_str(), &fileInfo) != 0)
		return false;
	if (permission)
   		return (S_ISREG(fileInfo.st_mode) && (fileInfo.st_mode & S_IXUSR));
	return S_ISREG(fileInfo.st_mode);
}

bool isValidAutoIndex(const std::string& autoindex)
{
	if (autoindex != "on" && autoindex != "off")
		return false;
	return true;
}

bool isValidUploadDir(const std::string& uploadDir)
{
	return isDirectory(uploadDir);
}
bool isValidRoot(const std::string& root)
{
	return isDirectory(root);
}

bool isValidClientBodyMaxSize(const std::string& clientBodyMaxSize)
{
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
	if (cp != 1)
		return false;
	for (; it != clientBodyMaxSize.rend(); ++it)
	{
		if (!std::isdigit(*it))
			return false;
	}
	return true;
}


bool isValidLocationPath(const std::string &uri)
{
	std::string::const_iterator it = uri.begin();

	int	cp = 0;
	
	while(it != uri.end() && *it == '/')
	{
		cp++;
		it++;
	}
	
	if (cp != 1)
		return false;
	
	// if (!isDirectory(uri))
	// 	return false;
	
	return true;
}

bool isValidLocationMethods(std::vector<std::string> &data)
{
	for (size_t i = 1; i < data.size(); i++)
	{
		if (data[i] != "POST" && data[i] != "DELETE" && data[i] != "GET")
			return false;		
	}
	return true;
}


bool isValidLocationCGI (const std::string &cgi, const std::string &cgiFile)
{
	if (cgi != "py" && cgi != "php")
		return false;

	if (!isFile(cgiFile, true))
		return false;
	return true;
}

bool isValidErrorPage(const std::string &err)
{
	Parsing w;
	std::vector<std::string> codes = w.getHttpStatusCodes();
	std::vector<std::string>::iterator it = std::find(codes.begin(), codes.end(), err);
	
	if (it == codes.end())
		return false;
	
	return true;
}
