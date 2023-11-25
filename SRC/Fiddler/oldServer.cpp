#include "../../includes/Request.hpp"

int    Request::createServer(Parsing &parsing)
{
    Server = parsing;

    if(SendFile)
    {
        offset = 0;
        std::ifstream file(RequestPath, std::ios::binary);
        if (!file)
            return (std::cerr << "Failed to open the file." << std::endl, 1);
        file.seekg(0, std::ios::end);
        FileSize = file.tellg();
        file.close();
        // std::cout << "FILESIZE: " << FileSize << std::endl;
    }
    else
    {
    }
    return(0);
}
