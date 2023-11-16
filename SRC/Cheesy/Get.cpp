#include "../../includes/Request.hpp"

int		Request::GetFile()
{
	if(locationIndex == 0)
		return(1);
	else
	{
		std::vector < std::pair <std::string, std::string > > srv = Server.getLocationMultiple(1, locationIndex, "cgi");
		if(srv.size())
		{
			//Run CGI on requested file
			// std::vector < std::pair <std::string, std::string > >::iterator srvIT = srv.begin();
		}
		else
		{
			ResponseHeaders = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
			std::fstream configFile;
			std::string fileName = RequestPath + File, str;

			ResponseBody.clear();
			configFile.open(fileName);
			if (!configFile)
				return (std::cerr << "Unable to open the file " << std::endl, statusCode = 404, 1);
			while (std::getline(configFile, str))
				ResponseBody += str;
		}
	}
	return(0);
}

int		Request::GetDirectory()
{
	std::vector < std::string> it;
	if(locationIndex != 0)
		it = Server.getLocationSingle(1, locationIndex, "index");
	if(it.size())//If index files are present
	{
		puts("HERE-------------");
		File = it[0];
		if(GetFile())
			return(1);
	}
	else//else check autoindex
	{
		std::string str = Server.getServerDataSingle(1, "autoindex");
		if(str == "off")
			return(statusCode = 403, 1);
		else if(str == "on")
		{
			ResponseHeaders = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
			
			std::fstream configFile;
			std::string fileName = "/Users/eamghar/Desktop/Webserv/SRC/Cheesy/index.html", str;

			ResponseBody.clear();

			configFile.open(fileName);
			if (!configFile)
				return (std::cerr << "Unable to open the file " << std::endl, 1);
			while (std::getline(configFile, str))
				ResponseBody += str;
		}
	}
	return(0);
}

int		Request::GET()
{
	struct stat fileStat;

	if(locationIndex != 0)// if found in location
	{
		std::vector < std::string> it = Server.getLocationSingle(1, locationIndex, "root");
		LocationRoot = it[0];
		if(URI != "/")
			RequestPath = LocationRoot + URI;
		else
			RequestPath = LocationRoot;	
	}
	else
		RequestPath = Server.getServerDataSingle(1, "root") + URI;
	if (stat(RequestPath.c_str(), &fileStat) == 0)
	{
		if (S_ISDIR(fileStat.st_mode))
			directory = 1;
		else if (S_ISREG(fileStat.st_mode))
			directory = 0;
		else
		{
			puts("here1");
			return(statusCode = 404, 1);
		}
	}
	else
		return(statusCode = 404, 1);

	std::cout << "GET PATH:" << RequestPath << " DIR: " << directory << std::endl;

	if(directory == 1 && (URI[URI.size() - 1] != '/' || URI != "/"))
		return(statusCode = 301, 1);
	if(URI[URI.size() - 1] == '/' || URI == "/")
	{
		std::cout << "DIR" << std::endl;
		if(GetDirectory())
			return(1);
	}
	else
	{
		std::cout << "File" << std::endl;
		File = URI;
		if(GetFile())
			return(1);
	}
	return(0);
}
