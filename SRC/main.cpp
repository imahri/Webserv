#include "../includes/Request.hpp"

int main(int ac, char **av)
{
    try
    {   
        //BUDA
        Webserv wbs;
       	if (!wbs.parsing(ac, av) || !wbs.fillServerList() || !wbs.finalConfigFileParsing())
		{
			std::cout << "GHALAAAAAAT" << std::endl;
			return 0;
		}
		wbs.fillResponseTypes();
			std::cout << "SA7777777" << std::endl;
	
		

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
