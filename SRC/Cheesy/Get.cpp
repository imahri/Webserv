#include "../../includes/Request.hpp"

int		Request::GetFile()
{

	return(0);
}

int		Request::GetDirectory()
{
	std::vector < std::string> it = Server.getLocationSingle(1, locationIndex, "index");
	if(it.size())//If index files are present
	{
		
	}
	else//else check autoindex
	{
		std::string str = Server.getServerDataSingle(1, "autoindex");
		if(str == "off")
			return(statusCode = 403, 1);
		else if(str == "on")
		{
			Response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n";
			
			std::fstream configFile;
			std::string fileName = "/Users/eamghar/Desktop/Webserv/SRC/Cheesy/index.html";
			std::string str;

			configFile.open(fileName);
			if (!configFile)
				return (std::cerr << "Unable to open the file " << std::endl, 1);
			while (std::getline(configFile, str))
				Response += str;
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
		LocationRoot = Server.getServerDataSingle(1, "root");

	std::cout << "DIR: " << LocationRoot << std::endl;
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
	// else
	// {
	// 	puts("here2");
	// 	return(statusCode = 404, 1);
	// }

	std::cout << "GET PATH:" << RequestPath << " DIR: " << directory << std::endl;

	if(URI[URI.size() - 1] == '/' || URI == "/")
	{
		std::cout << "DIR" << std::endl;
		if(GetDirectory())
			return(1);
	}
	else
	{
		std::cout << "File" << std::endl;
		if(GetFile())
			return(1);
	}
	return(0);
}
