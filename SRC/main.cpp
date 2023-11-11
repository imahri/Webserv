#include "../includes/Request.hpp"

int main(int ac, char **av)
{
    //BUDA
    Webserv wbs;
	wbs.parsing(ac, av);
	wbs.fillServerList();

	// std::cout << wbs.getServersNumber() << std::endl;

	// // std::cout << webServ.getLocationsNumber(0) << std::endl;


	// std::vector < std::pair <std::string, std::vector < std::string > > > locationData = webServ.getLocationData(1, 1);
	// for (std::vector<std::pair<std::string, std::vector<std::string> > >::iterator it = locationData.begin(); it != locationData.end(); ++it)
	// {
	// 	std::cout << it->first << std::endl;
	// 	for (std::vector<std::string>::iterator innerIt = it->second.begin(); innerIt != it->second.end(); ++innerIt) 
	// 	{
	// 		std::cout << *innerIt << " ";
	// 	}
	// 	std::cout << std::endl;
	// 	std::cout << "--------------------------" <<std::endl;
	// }

	// std::vector < std::string > data = wbs.getLocationSpecificData(1,1,"methods");

	// for (size_t i = 0; i < data.size(); i++)
	// {
	// 	std::cout << data[i] << std::endl;
	// }
	
	std::vector < std::pair <std::string, std::string > > data = wbs.getLocationSpecificDatas(1,1,"error_page");
	for (size_t i = 0; i < data.size(); i++)
	{
		std::cout << data[i].first << "   " << data[i].second << std::endl;
	}

    //CHEESY
    // Request     rq;

	
    // if(rq.createServer(wbs))
    //     return(1);

    return 0;
}
