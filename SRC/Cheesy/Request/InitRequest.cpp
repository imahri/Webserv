#include "../../../includes/Request.hpp"

int     Request::InitRequest(std::string str)
{
    offset = 0;
    RequestIsDone = false;
    ClientIsDone = false;
    PathToSaveFile = "/Users/eamghar/Desktop/send";
    ResponseHeaders.clear();
    ResponseBody.clear();
    this->getRequest(str);
    std::cout << "StatusCode: " << statusCode << std::endl;
    GenerateResponse();
    return(0);
}


