#include "../includes/Request.hpp"

int main(int ac, char **av)
{
    try
    {   
        //BUDA
        Webserv wbs;
        wbs.parsing(ac, av);
        wbs.fillServerList();

		wbs.finalParsing();


		// std::vector < std::pair < std::string, std::string > >	data = wbs.getServerErrorPages(2);
		// std::vector < std::pair < std::string, std::string > >::iterator it =	data.begin();
		
		// for (; it != data.end(); it++)
		// {
		// 	std::cout << it->first << "   " << it->second << std::endl;
			
		// }
		

        //CHEESY
        // Request     rq;

        
        // if(rq.createServer(wbs))
        //     return(1);

    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    return 0;
}
