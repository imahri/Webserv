#include "../includes/Webserv.hpp"

int main(int ac, char **av)
{
    try
    {
        Parsing wbs;
       	if (!wbs.parsing(ac, av) || !wbs.fillServerList() || !wbs.finalConfigFileParsing())
			return (std::cout << "ERROR IN CONFIG FILE." << std::endl, 1);
		wbs.fillResponseTypes();

        std::cout << "--------------->" << wbs.getServerServerName("server_name", "testddd.com") << std::endl;
        IoMultiplexing io;
        if(io.StartTheMatrix(wbs))
            return(1);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << std::endl;
    }
    return 0;
}
