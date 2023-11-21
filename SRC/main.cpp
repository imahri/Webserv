#include "../includes/Request.hpp"

int main(int ac, char **av)
{
    try
    {   
        //BUDA
        Webserv wbs;
       	if (!wbs.parsing(ac, av) || !wbs.fillServerList() || !wbs.finalConfigFileParsing())
			return (std::cout << "ERROR IN CONFIG FILE." << std::endl, 1);
		wbs.fillResponseTypes();

        //CHEESY
        Request     rq;

        if(rq.createServer(wbs))
            return(1);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
