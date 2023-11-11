#include "../includes/Request.hpp"

int main(int ac, char **av)
{
    //BUDA
    Webserv webServ;
	webServ.parsing(ac, av);
	webServ.fillServerList();

	// // std::cout << webServ.getLocationsNumber(0) << std::endl;


	std::vector < std::pair <std::string, std::vector < std::string > > > locationData = webServ.getLocationData(1, 1);
	for (std::vector<std::pair<std::string, std::vector<std::string> > >::iterator it = locationData.begin(); it != locationData.end(); ++it)
	{
		std::cout << it->first << std::endl;
		for (std::vector<std::string>::iterator innerIt = it->second.begin(); innerIt != it->second.end(); ++innerIt) 
		{
			std::cout << *innerIt << " ";
		}
		std::cout << std::endl;
		std::cout << "--------------------------" <<std::endl;
	}
    //CHEESY
    Request     rq;

    if(rq.createServer())
        return(1);

    return 0;
}
