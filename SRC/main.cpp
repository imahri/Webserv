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
