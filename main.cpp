#include "Request.hpp"

int main()
{
    Request     rq;

    if(rq.createServer())
        return(1);
    return 0;
}
