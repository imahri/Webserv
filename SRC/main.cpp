#include "../includes/Webserv.hpp"

void    d()
{
    system("leaks Webserv");
}

int main(int ac, char **av)
{
    atexit(d);
    try
    {
        Parsing wbs;
       	if (!wbs.parsing(ac, av) || !wbs.fillServerList() || !wbs.finalConfigFileParsing())
			return (std::cout << "ERROR IN CONFIG FILE." << std::endl, 1);
		wbs.fillResponseTypes();

        // std::cout << "--------------->" << wbs.getServerServerName("listen", "127.0.0.1:144") << std::endl;
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
