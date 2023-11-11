#include "../includes/Request.hpp"

int main(int ac, char **av)
{
    //BUDA
    Webserv wbs;
	wbs.parsing(ac, av);
	wbs.fillServerList();

    //CHEESY
    Request     rq;

	
    if(rq.createServer(wbs))
        return(1);

    return 0;
}
