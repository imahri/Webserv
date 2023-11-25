#include "../includes/Webserv.hpp"

int main(int ac, char **av)
{
    try
    {
        // BUDA
        Parsing wbs;
       	if (!wbs.parsing(ac, av) || !wbs.fillServerList() || !wbs.finalConfigFileParsing())
			return (std::cout << "ERROR IN CONFIG FILE." << std::endl, 1);
		wbs.fillResponseTypes();


        IoMultiplexing io;
        //FIDDLER
        if(io.StartTheMatrix(wbs))
            return(1);

        //CHEESY
        // Request     rq;

        // if(rq.createServer(wbs))
        //     return(1);
        
        // IoMultiplexing io;
        // io.StartTheMatrix();
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
