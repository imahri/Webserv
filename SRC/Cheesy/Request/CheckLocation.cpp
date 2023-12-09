#include "../../../includes/Request.hpp"

int		Request::GetCorrectLocation()
{
	std::string str;
	locationIndex = 0;
	locationIndex = Server.checkForLocation(ServerIndex, URI);
	if(locationIndex == -1)
	{
		locationIndex = Server.checkForLocation(ServerIndex, "/");
		if(locationIndex == -1)
			locationIndex = 0;
	}
	
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

		Loc.error_page = Server.getServerErrorPages(ServerIndex);
		if(Loc.error_page.size())
			Loc.CheckErrorPage = true;
		
        Loc.client_body_max_size = convertToCharacters(Server.getServerDataSingle(ServerIndex, "client_body_max_size"));
	}
	else
	{
		std::vector < std::string >	it;
		if(Server.getServerDataSingle(ServerIndex, "autoindex") == "on")
			Loc.autoindex = true;
		else
			Loc.autoindex = false;

		it = Server.getLocationSingle(ServerIndex, locationIndex, "index");
		if(it.size())
		{
			Loc.CheckIndex = true;
        	Loc.index = *it.begin();
		}
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

		it = Server.getLocationSingle(ServerIndex, locationIndex, "upload_dir");
		if(it.size())
		{
			Loc.CheckUploadDir = true;
        	Loc.upload_dir = *it.begin();
		}
		else
			Loc.CheckUploadDir = false;
			
		it = Server.getLocationSingle(ServerIndex, locationIndex, "root");
        Loc.root = *it.begin();

		it = Server.getLocationSingle(ServerIndex, locationIndex, "client_body_max_size");
        Loc.client_body_max_size = convertToCharacters(*it.begin());

		Loc.error_page = Server.getLocationMultiple(ServerIndex, locationIndex, "error_page");
		if(Loc.error_page.size())
			Loc.CheckErrorPage = true;
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
			ResponseBody.clear();
			ResponseBody = "<meta http-equiv=\"Refresh\" content=\"0; url='" + it->second + "'\" />\r\n";
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

	return(0);
}
