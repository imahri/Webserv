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

		std::cout << ( wbs.finalConfigFileParsing() ? "true" : "false" ) << std::endl;

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
