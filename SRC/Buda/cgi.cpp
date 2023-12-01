
/*
Can be Obtained from Request Headers:

	*>REQUEST_METHOD
	*>CONTENT_LENGTH
	*>CONTENT_TYPE

	>HTTP_COOKIE
	>HTTP_ACCEPT
	>HTTP_ACCEPT_LANGUAGE
	>HTTP_REFERER
	>HTTP_USER_AGENT
	>HTTP_ACCEPT_ENCODING
	>HTTP_ACCEPT_CHARSET


Set by the Web Server or CGI Handler:

	*>PATH_INFO
	*>SCRIPT_FILENAME
	*>QUERY_STRING

	>REDIRECT_STATUS
	>REQUEST_URI
	>PATH_TRANSLATED
	>GATEWAY_INTERFACE
	>SERVER_SOFTWARE
	>REMOTE_HOST
	>SERVER_NAME
	>SERVER_PROTOCOL
	>AUTH_TYPE
	>DOCUMENT_ROOT
	>UPLOAD_PATH
	>SERVER_PORT
*/


/*
	//header
		POST /example/path?param1=value1&param2=value2 HTTP/1.1
		Host: example.com
		Cookie: user_session=abc123; preferences=dark-mode
		Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,**;q=0.8
		Accept-Language: en-US,en;q=0.9
		Referer: https://referrer.com/page
		User-Agent: Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36
		Accept-Encoding: gzip, deflate, br
		Accept-Charset: utf-8, iso-8859-1;q=0.5
		Content-Type: application/json
		Content-Length: 56


		Host: localhost:6969
		Connection: keep-alive
		sec-ch-ua: "Google Chrome";v="119", "Chromium";v="119", "Not?A_Brand";v="24"
		sec-ch-ua-mobile: ?0
		sec-ch-ua-platform: "macOS"
		DNT: 1
		Upgrade-Insecure-Requests: 1
		User-Agent: Mozilla/5.0 (Macintosh; Intel Mac OS X 10_15_7) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/119.0.0.0 Safari/537.36
		Accept: text/html,application/xhtml+xml,application/xml;q=0.9,image/avif,image/webp,image/apng,/;q=0.8,application/signed-exchange;v=b3;q=0.7
		Sec-Fetch-Site: none
		Sec-Fetch-Mode: navigate
		Sec-Fetch-User: ?1
		Sec-Fetch-Dest: document
		Accept-Encoding: gzip, deflate, br
		Accept-Language: en-US,en;q=0.9,fr;q=0.8


	//body
		{"key1": "value1", "key2": "value2", "key3": "value3"}
*/

// ["SERVER_PORT"]					== req port +						=>	80
// ["SERVER_NAME"]					== "OreO"							=>	OreO
// ["REQUEST_METHOD"]				== req mathod+						=>	POST
// ["QUERY_STRING"]					== req query+						=>	param1=value1&param2=value2
// ["SERVER_PROTOCOL"]				== ?+								=>	HTTP/1.1
// ["PATH_INFO"]					== 1 line in the header				=>	example/path
// ["REQUEST_URI"]					== 1 line in the header+			=>	/example/path?param1=value1&param2=value2
// ["SCRIPT_FILENAME"]				== script file						=>	/SRC/BUDA/CGI_BIN/php-cgi
// ["CONTENT_LENGTH"]				== req body len+					=>	56
// ["CONTENT_TYPE"]					== req type+						=>	application/json
// ["REDIRECT_STATUS"]				== 200+								=>	200
// ["HTTP_COOKIE"]					== header Cookies					=>	user_session=abc123; preferences=dark-mode
// ["GATEWAY_INTERFACE"]			== "CGI/1.1"						=>	CGI/1.1
// ["PATH_TRANSLATED"] 				== ?								=>	/var/www/html/path/to/resource
// ["HTTP_ACCEPT"]					== header Accept					=>	text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,image/apng,**;q=0.8
// ["UPLOAD_PATH"]					== upload dir form the config +		=>	/var/www/uploads
// ["HTTP_ACCEPT_LANGUAGE"]			== header Accept-Language			=>	en-US,en;q=0.9
// ["HTTP_REFERER"]					== Referer							=>	https://referrer.com/page
// ["AUTH_TYPE"]					== "Basic" +						=>	Basic
// ["SERVER_SOFTWARE"]				== "webserv/test/1.0"				=>	webserv/test/1.0
// ["REMOTE_HOST"]					== 127.0.0.1						=>	127.0.0.1
// ["HTTP_USER_AGENT"]				== req User-Agent +					=>	Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36
// ["HTTP_ACCEPT_ENCODING"]			== req Accept-Encoding				=>	gzip, deflate, br
// ["DOCUMENT_ROOT"]				== ?								=>	/var/www/html

/* req example

------------------------------------------------------------
// POST /cgi-bin/your_cgi_script HTTP/1.1
// Host: yourdomain.com
// Content-Type: application/json
// Content-Length: 42

// {"key": "value", "another_key": "another_value"}
------------------------------------------------------------

*/


// fill env

// // fill args
// 	// char[3] =
// 		/bin/php,				// jibo mn xi blasa
// 		/www/site/index.php,    // ktb dyalek
// 		null
// 	}
// 	exeve(bin_path, char[3], env_li3mrna);
// 	 // keep pid for polllout


// #include <fcntl.h>
// #include <unistd.h>
// #include <cstdlib>
// #include <sys/wait.h>
// #include <sstream>
// #include <cstring>
// #include <cstdio>
// void test()
// {
// 	// FILE *fIn = tmpfile();
// }
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
	this->cgiENV["REMOTE_HOST"] = "127.0.0.1";
	this->cgiENV["REQUEST_METHOD"] = cgi.methode;
	this->cgiENV["SERVER_PROTOCOL"] = cgi.httpVersion;
	this->cgiENV["REDIRECT_STATUS"] = std::to_string(cgi.CodeStatus);
	this->cgiENV["QUERY_STRING"] = cgi.Query;
	this->cgiENV["SCRIPT_NAME"] = cgi.RequestPath;
	this->cgiENV["SCRIPT_FILENAME"] = cgi.RequestPath;

	this->cgiENV["HTTP_ACCEPT_ENCODING"] = getEnvHeader("Accept-Encoding");
	this->cgiENV["HTTP_USER_AGENT"] = getEnvHeader("User-Agent");
	this->cgiENV["HTTP_COOKIE"] = getEnvHeader("Cookie");
	this->cgiENV["HTTP_ACCEPT"] = getEnvHeader("Accept");
	this->cgiENV["HTTP_ACCEPT_LANGUAGE"] = getEnvHeader("Accept-Language");
	this->cgiENV["HTTP_REFERER"] = getEnvHeader("Referer");
	this->cgiENV["CONTENT_LENGTH"] = getEnvHeader("Content-Length");
	this->cgiENV["CONTENT_TYPE"] = getEnvHeader("Content-Type");

	std::string s = getEnvHeader("Host");
	this->cgiENV["SERVER_PORT"] = ft_split(s, ':')[1];

	this->cgiENV["PATH_TRANSLATED"] = cgi.RequestPath;
	this->cgiENV["PATH_INFO"] = cgi.URI;



	// this->cgiENV["PATH_TRANSLATED"] = "/Users/ytaqsi/Desktop/";
	// this->cgiENV["PATH_INFO"] = "/";
	// this->cgiENV["PATH_INFO"] = path_info;
	// this->cgiENV["PATH_TRANSLATED"] = root + path_info;
}

void	Parsing::splitHeaders()
{
	if (headers.size())
		headers.clear();
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


void	Parsing::convertMap()
{
	std::map< std::string, std::string >::iterator it = cgiENV.begin();
	execEnv = new char *[cgiENV.size() + 1];
	size_t i = 0;
	size_t j;
	for (; it != cgiENV.end(); it++)
	{
		std::string s = it->first + "=" + it->second;
		execEnv[i] = new char[s.length() + 1];
		j = 0;
		for (; j < s.length(); j++)
			execEnv[i][j] = s[j];
		execEnv[i][j] = '\0';
		i++;
	}
	execEnv[i] = NULL;
}

#include <sys/time.h>
std::string	getFileName()
{
	struct timeval tv;
    gettimeofday(&tv, NULL);
    long long milliseconds = static_cast<long long>(tv.tv_sec) * 1000 + tv.tv_usec / 1000;

	std::ostringstream oss;
    oss << milliseconds;
    
    return oss.str();
}

std::string   Parsing::handleCGIres(const std::string& outFileName)
{
	

	// red the output file and store the content in the res
	std::ifstream resFile(outFileName.c_str(), std::ios::binary);
	if (!resFile.is_open())
		std::cerr << "Error opening file: " << outFileName << std::endl;
	
	std::stringstream iss;
	iss << resFile.rdbuf();

	std::cout << "-----------------------------------------------CGI Res-----------------------------------------" << std::endl;

	// check if correct header



		// std::cout << iss.str() << std::endl;
		std::string line;
		std::string resHeaders;
		std::string resBody;
		bool		header = true;
		while(std::getline(iss, line))
		{
			if (line.empty() || line == "\r" || line == "\r\n" || line == "\r\n\r\n")
				header = false;

			if (header)
			{
				if (line.find(':') == std::string::npos)
					return "Content-Type: text/plain\r\nStatus: 400 Bad Request\r\n\r\nBad Request: Invalid headers\r\n";
				resHeaders += line;
			}
			else
				resBody += line;
		}
		cgi.header = resHeaders;
		splitHeaders();
		headers["Content-Length"] = std::to_string(resBody.length());

	std::cout << "-----------------------------------------------CGI Res headers-----------------------------------------" << std::endl;

	std::cout << "-----------------------------------------------CGI Res headers end-----------------------------------------" << std::endl;
	// 	std::cout << resHeaders << std::endl;
	// std::cout << "-----------------------------------------------CGI Res Body-----------------------------------------" << std::endl;
	// 	std::cout << resBody << std::endl;

		std::cout << iss.str() << std::endl;
	std::cout << "-----------------------------------------------CGI end Res-----------------------------------------" << std::endl;



	// close all files
	resFile.close();

	// remove all files
	std::remove(outFileName.c_str());
	// std::remove(inFileName.c_str());
	// return resBody;
	return iss.str();
}

std::string  Parsing::CgiResult(CGI &c)
{

	cgi = c;
	splitHeaders();
	envInit();
	convertMap();

	// in and out files
	// std::string inFileName = "inFile" + getFileName();
	std::string outFileName = "/tmp/outFile" + getFileName();

	// av
	char *av[3];
    av[0] = (char *)this->cgi.locationData.cgi[0].second.c_str();
    av[1] = (char *)cgi.RequestPath.c_str();
    av[2] = NULL;

	// in and out backup
	int outBackUp = dup(STDOUT_FILENO);
	int outFileFD = open(outFileName.c_str(), O_WRONLY | O_CREAT, 0777);

    if (outFileFD == -1)
        perror("open");

	// exe the cgi
	int pid = fork();
	if (pid == 0)
	{
		if (dup2(outFileFD, STDOUT_FILENO) == -1)
			perror("dup2");

		execve(av[0], av, execEnv);
		std::cerr << "------------------------------------------l*waaaaaaaaaa------------------------------------------------" << std::endl;
	}
	// wait and return the original val of fds
	waitpid(pid, NULL, 0);
	dup2(outBackUp, 1);
    close(outFileFD);


	// for cgi res
	std::string resBody = handleCGIres(outFileName);
	// free the env
	if (execEnv != nullptr) 
	{
        for (size_t i = 0; execEnv[i] != nullptr; ++i)
            delete[] execEnv[i];
        delete[] execEnv;
    }
	
	return(resBody);
};
