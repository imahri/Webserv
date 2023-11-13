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
		// std::vector < std::pair <std::string, std::vector < std::string > > > VEC	 = Server.serverData(1);
		// std::vector < std::pair <std::string, std::vector < std::string > > >::iterator	 iter = VEC.begin();

		std::cout << "----------------------GETDIR----------------------------" << std::endl;

		// for (; iter != VEC.end(); iter++)
		// {
		// 	std::cout << "FIRST-->|" << iter->first << std::endl;
		// 	std::vector < std::string >::iterator itSecond = iter->second.begin();
		// 	for (; itSecond != iter->second.end(); itSecond++)
		// 		std::cout << "Second-->|" << *itSecond << std::endl;
		// }
	}

	return(0);
}

int		Request::GET()
{
    struct stat fileStat;

	std::vector < std::string> it = Server.getLocationSingle(1, locationIndex, "root");
    if (stat(it[0].c_str(), &fileStat) != 0)
		return(statusCode = 404, 1);

	LocationRoot = it[0];

    if (stat(URI.c_str(), &fileStat) == 0)
	{
        if (S_ISDIR(fileStat.st_mode))
            directory = 1;
        else if (S_ISREG(fileStat.st_mode))
            directory = 0;
        else
			return(statusCode = 301, 1);
    }
	else
		return(statusCode = 404, 1);

	if(URI[URI.size() - 1] == '/')
	{
		if(GetDirectory())
			return(1);
	}
	else
		if(GetFile())
			return(1);

	return(0);
}