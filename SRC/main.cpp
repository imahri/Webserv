#include "../includes/Request.hpp"

int main(int ac, char **av)
{
    try
    {   
        //BUDA
        Webserv wbs;
       	if (!wbs.parsing(ac, av))
			return 0;
        wbs.fillServerList();
		wbs.fillResponseTypes();

		// std::string result = wbs.getServerDataSingle(1, "autoindex");
		// std::cout << result << std::endl;
		std::cout << ( wbs.finalConfigFileParsing() ? "true" : "false" ) << std::endl;
		// std::cout << wbs.checkForLocation(1, "/assets") << std::endl;


		// std::vector < std::pair < std::string, std::string > >	data = wbs.getServerErrorPages(2);
		// std::vector < std::pair < std::string, std::string > >::iterator it =	data.begin();
		
		// for (; it != data.end(); it++)
		// {
		// 	std::cout << it->first << "   " << it->second << std::endl;
			
		// }
		

        //CHEESY
        Request     rq;

        
        if(rq.createServer(wbs))
            return(1);
		


    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
