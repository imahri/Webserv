#include "../../../includes/Request.hpp"

int		Request::GetCorrectLocation()
{
	std::string str;
	locationIndex = 0;
	locationIndex = Server.checkForLocation(ServerIndex, URI);
	if(locationIndex == 0)
	{
		if(Server.getServerDataSingle(ServerIndex, "autoindex") == "on")
			Loc.autoindex = true;
		else
			Loc.autoindex = false;

		Loc.CheckIndex = false;
        Loc.CheckCGI = false;
		Loc.CheckMethods = false;
        Loc.CheckRedirect = false;
        Loc.upload_dir = Server.getServerDataSingle(ServerIndex, "upload_dir");
        Loc.root = Server.getServerDataSingle(ServerIndex, "root");

        Loc.client_body_max_size = convertToCharacters(Server.getServerDataSingle(ServerIndex, "client_body_max_size"));
	}
	else
	{
		if(Server.getServerDataSingle(ServerIndex, "autoindex") == "on")
			Loc.autoindex = true;
		else
			Loc.autoindex = false;

        Loc.index = Server.getLocationSingle(ServerIndex, locationIndex, "index");
		if(Loc.index.size())
			Loc.CheckIndex = true;
		else
			Loc.CheckIndex = false;

		Loc.methodes = Server.getLocationSingle(ServerIndex, locationIndex, "methods");
		if(Loc.methodes.size())
			Loc.CheckMethods = true;
		else
			Loc.CheckMethods = false;

		Loc.cgi = Server.getLocationMultiple(ServerIndex, locationIndex, "cgi");
		if(Loc.cgi.size())
			Loc.CheckCGI = true;
		else
			Loc.CheckCGI = false;

		Loc.redirect = Server.getLocationMultiple(ServerIndex, locationIndex, "redirect");
		if(Loc.redirect.size())
			Loc.CheckRedirect = true;
		else
			Loc.CheckRedirect = false;

		std::vector < std::string >	it = Server.getLocationSingle(ServerIndex, locationIndex, "upload_dir");
        Loc.upload_dir = *it.begin();

		it = Server.getLocationSingle(ServerIndex, locationIndex, "root");
        Loc.root = *it.begin();

		it = Server.getLocationSingle(ServerIndex, locationIndex, "client_body_max_size");
        Loc.client_body_max_size = convertToCharacters(*it.begin());
	}

	return(0);
}

int		Request::checkLocations()
{
	if(GetCorrectLocation())
		return(1);

    if(Loc.CheckRedirect == true)
    {
        std::vector < std::pair <std::string , std::string > >::iterator it = Loc.redirect.begin();
        for (; it != Loc.redirect.end(); it++)
        {
			ResponseHeaders = "HTTP/1.1 302 OK\r\nContent-Type: text/html\r\n\r\n";
			ResponseBody += "<meta http-equiv=\"Refresh\" content=\"0; url='" + it->second + "'\" />";
			return(statusCode = std::atoi(it->first.c_str()), 1);
        }
    }

	size_t i = 0;
	if(Loc.CheckMethods == true)
	{
		for (i = 0; i < Loc.methodes.size(); i++)
			if(methode == Loc.methodes[i])
				break;
		if(i == Loc.methodes.size())
			return(statusCode = 405, 1);
	}


	// std::cout << "TESTING BUDA'S SHIT" << std::endl;

	// std::map < std::string, std::vector < std::string > >::iterator	it = Server.responseTypes.begin();
	
	// Server.responseTypes.lower_bound
	// for (; it != Server.responseTypes.end(); it++)
	// {
	// 	std::cout << "first: " << it->first << std::endl;
	// 	for (std::vector < std::string >::iterator it2 = it->second.begin(); it2 != it->second.end(); it2++)
	// 		std::cout << "second: " << *it2 << std::endl;
	// }
	
	// std::cout << "END OF TESTING BUDA'S SHIT" << std::endl;
	return(0);
}
