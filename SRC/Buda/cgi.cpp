#include "../../includes/Webserv.hpp"

std::string	Parsing::getEnvHeader(const std::string&  s)
{
    std::map<std::string, std::string>::iterator	i = this->headers.begin();
	for (; i != headers.end(); i++)
	{
		if (s == i->first)
			return i->second;
	}
	return "";
}

void	 Parsing::envInit()
{
	this->cgiENV["SERVER_NAME"] = "OreO";
	this->cgiENV["GATEWAY_INTERFACE"] = "CGI/1.1";
	this->cgiENV["AUTH_TYPE"] = "Basic";
	this->cgiENV["SERVER_SOFTWARE"] = "webserv/test/1.0";

	this->cgiENV["HTTP_ACCEPT_ENCODING"] = getEnvHeader("Accept-Encoding");
	this->cgiENV["HTTP_USER_AGENT"] = getEnvHeader("User-Agent");
	this->cgiENV["HTTP_COOKIE"] = getEnvHeader("Cookie");
	this->cgiENV["HTTP_ACCEPT"] = getEnvHeader("Accept");
	this->cgiENV["HTTP_ACCEPT_LANGUAGE"] = getEnvHeader("Accept-Language");
	this->cgiENV["HTTP_REFERER"] = getEnvHeader("Referer");

	this->cgiENV["CONTENT_LENGTH"] = getEnvHeader("Content-Length");
	this->cgiENV["CONTENT_TYPE"] = getEnvHeader("Content-Type");
	std::string s = getEnvHeader("Host");
	if (s.size())
	{
		std::vector <std::string> v =  ft_split(s, ':');
		this->cgiENV["REMOTE_HOST"] = v[0];
		this->cgiENV["SERVER_PORT"] = v[1];
	}

	this->cgiENV["REQUEST_METHOD"] = cgi.methode;
	this->cgiENV["SERVER_PROTOCOL"] = cgi.httpVersion;
	this->cgiENV["REDIRECT_STATUS"] = toString(cgi.CodeStatus);
	this->cgiENV["QUERY_STRING"] = cgi.Query;
	this->cgiENV["SCRIPT_NAME"] = cgi.RequestPath;
	this->cgiENV["SCRIPT_FILENAME"] = cgi.RequestPath;
	this->cgiENV["PATH_INFO"] = cgi.URI;
}

void	Parsing::splitHeaders()
{
	std::vector <std::string> s = ft_split(cgi.header, "\n\r");
	for (size_t i = 0; i < s.size(); i++)
	{
		size_t f = s[i].find(':');
		if (f != std::string::npos)
		{
			std::string key = s[i].substr(0, f);
			std::string val =  s[i].substr(f + 2);
			headers[key] = val;
		}
	}
	s.clear();
}


bool	Parsing::convertMap()
{
	std::map< std::string, std::string >::iterator it = cgiENV.begin();
	execEnv = new char *[cgiENV.size() + 1];
	if (execEnv == NULL)
	{
		clearCGI("500");
		return false;
	}
	size_t i = 0;
	size_t j;
	for (; it != cgiENV.end(); it++)
	{
		std::string s = it->first + "=" + it->second;
		execEnv[i] = new char[s.length() + 1];
		if (execEnv[i] == NULL)
		{
			for (size_t j = 0; j < i; j++)
				delete[] execEnv[j];
			delete[] execEnv;
			clearCGI("500");
			return false;
		}
		j = 0;
		for (; j < s.length(); j++)
			execEnv[i][j] = s[j];
		execEnv[i][j] = '\0';
		i++;
	}
	execEnv[i] = NULL;
	return true;
}

std::string	getFileName()
{
	struct timeval tv;
    gettimeofday(&tv, NULL);
    long long milliseconds = static_cast<long long>(tv.tv_sec) * 1000 + tv.tv_usec / 1000;

	std::ostringstream oss;
    oss << milliseconds;
    
    return oss.str();
}

void   Parsing::handleCGIres(const std::string& outFileName)
{
	std::ifstream resFile(outFileName.c_str(), std::ios::binary);
	if (!resFile.is_open())
	{
		clearCGI("500");
		return ;
	}
	if (resFile.peek() == std::ifstream::traits_type::eof()) 
	{
		clearCGI("500");
		return ;
	}
	resFile.seekg(0, std::ios::beg);
	std::stringstream iss;
	iss << resFile.rdbuf();
	std::vector<std::string> respo = Divide(iss.str(), "\r\n\r\n");
	if (respo.size() != 2)
	{
		clearCGI("500");
		return ;
	}
	std::vector<std::string> resHeader = Divide(respo[0], "\r\n");

	int		cpForCL = 0;
	int		cpForCT = 0;
	std::string contentLenght;
	for (size_t i = 0; i < resHeader.size(); i++)
	{
		size_t f = resHeader[i].find(':');
		if (f == std::string::npos)
		{
			clearCGI("502");
			return;
		}
		std::string key = resHeader[i].substr(0, f + 1);
		std::string val =  resHeader[i].substr(f + 2);
		cgi.ret.mapap.push_back(std::make_pair(key, val));
		for (size_t j = 0; j < key.length(); j++)
			key[j] = std::tolower(key[j]);
		if (key == "content-type:")
			cpForCT++;
		if (key == "content-length:")
		{
			cpForCL++;
			contentLenght = resHeader[i].substr(f + 2);
		}
	}
	if (cpForCT != 1)
	{
		clearCGI("502");
		return ;
	}
	if (cpForCL > 1)
	{
		clearCGI("502");
		return ;
	}
	if (cpForCL == 1 && std::atoi(contentLenght.c_str()) != (int)respo[1].length() - 2)
	{
		clearCGI("502");
		return ;
	}

	if (cpForCL)
		cgi.ret.body = respo[1].substr(0, std::atoi(contentLenght.c_str())) + "\r\n";
	else
		cgi.ret.body = respo[1] + "\r\n";

	if (!cpForCL)
		cgi.ret.mapap.push_back(std::make_pair("Content-Length:", toString(cgi.ret.body.length() - 2)));
		
	cgi.ret.header.clear();
	for (size_t i = 0; i < cgi.ret.mapap.size(); i++)
		cgi.ret.header += cgi.ret.mapap[i].first + " " + cgi.ret.mapap[i].second + "\r\n";
	cgi.ret.header += "\r\n";

	resFile.close();
	std::remove(outFileName.c_str());
}

void	Parsing::freeENV()
{
	if (execEnv != NULL) 
	{
        for (size_t i = 0; execEnv[i] != NULL; ++i)
            delete[] execEnv[i];
        delete[] execEnv;
    }
}
void	Parsing::clearCGI(const std::string& code)
{
	cgi.ret.code = code;
	cgi.ret.mapap.clear();
	cgi.ret.header.clear();
	cgi.ret.body.clear();
}


Rawr  Parsing::CgiResult(CGI &c)
{

	cgi = c;
	splitHeaders();
	envInit();
	if (!convertMap())
		return cgi.ret;
	
	int inFileFD;
	bool ifBody = false;
	std::map<std::string, std::string>::iterator it = cgiENV.find("CONTENT_LENGTH");
	std::string inFileName = "/tmp/inFile" + getFileName();
	if (!it->second.empty())
	{
		std::ofstream outFile(inFileName.c_str());
		outFile << cgi.body;
		outFile.close();
		inFileFD = open(inFileName.c_str(), O_WRONLY, 0777);
		ifBody = true;
	}

	std::string outFileName = "/tmp/outFile" + getFileName();

	char *av[3];
    av[0] = (char *)this->cgi.locationData.cgi[0].second.c_str();
    av[1] = (char *)cgi.RequestPath.c_str();
    av[2] = NULL;

	int inBackUp = dup(STDIN_FILENO);
	int outBackUp = dup(STDOUT_FILENO);

	int outFileFD = open(outFileName.c_str(), O_WRONLY | O_CREAT, 0777);

    if (outFileFD == -1)
        return (freeENV(),  clearCGI("500"), cgi.ret);

	int pid = fork();
	if (pid == 0)
	{
		if (dup2(outFileFD, STDOUT_FILENO) == -1)
			exit(500);
		if (ifBody)
			dup2(inFileFD, STDIN_FILENO);
		alarm(30);
		execve(av[0], av, execEnv);
		exit(500);
	}

	int status;
	waitpid(pid, &status, 0);
	if (dup2(outBackUp, 1) == -1)
		return (freeENV(),  clearCGI("500"), cgi.ret);
	if (dup2(inBackUp, 0) == -1)
		return (freeENV(),  clearCGI("500"), cgi.ret);
	close(outFileFD);
	if (ifBody)
		close(inFileFD);
	if (WIFEXITED(status))
	{
		int exit_code = WEXITSTATUS(status);
		if (exit_code == 0)
			cgi.ret.code = "200";
		else
			return (freeENV(), clearCGI("500"), cgi.ret);
	}
	else if (WIFSIGNALED(status))
		return (freeENV(), clearCGI("504"), cgi.ret);

	handleCGIres(outFileName);
	if (ifBody)
		std::remove(inFileName.c_str());
	return (freeENV(), cgi.ret);
};
