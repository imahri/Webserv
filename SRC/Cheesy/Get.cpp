#include "../../includes/Request.hpp"

int		Request::GetFile()
{

	return(0);
}

int		Request::GetDirectory()
{
	std::vector < std::string> it = Server.getLocationSingle(1, locationIndex, "index");
	if(it.size())
	{
		
	}
	else
	{
		std::string str = Server.getServerDataSingle(1, "autoindex");
		if(str == "off")
			return(statusCode = 403, 1);
		// else

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
