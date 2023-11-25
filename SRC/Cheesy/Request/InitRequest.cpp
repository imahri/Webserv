#include "../../../includes/Request.hpp"

void    Request::Reset()
{
    HeaderData.clear();
    header.clear();
    body.clear();
    line.clear();
    http.clear();
    httpVersion.clear();
    methode.clear();
    URI.clear();
    RequestPath.clear();
    ResponseHeaders.clear();
    ResponseBody.clear();
    index = 0;
    statusCode = 200;
    locationIndex = 0;
    IsDirectory = 0;
    File.clear();
    UploadDir.clear();
    PathToSaveFile.clear();
    ds.clear();
    ServerIndex = 1;
    bzero(&Loc, sizeof(LOCATION));
    bzero(&Req, sizeof(Response));
    SendFile = 0;
    FileSize = 0;
    offset = 0;
    ClientIsDone = false;
    RequestIsDone = false;
    PathToSaveFile = "/Users/eamghar/Desktop/send";
}

int     Request::InitRequest(std::string str, int j, Parsing &ps)
{
    Reset();
    Server = ps;
    ServerIndex = j;
    std::cout << "------------------------------------------------------------------1" << std::endl;
    this->getRequest(str);
    std::cout << "------------------------------------------------------------------2" << std::endl;
    std::cout << "StatusCode: " << statusCode << std::endl;
    GenerateResponse();
    return(0);
}


