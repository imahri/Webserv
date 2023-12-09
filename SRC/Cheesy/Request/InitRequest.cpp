#include "../../../includes/Request.hpp"

void    Request::Reset()
{
    bzero(&Loc, sizeof(LOCATION));
    bzero(&Req, sizeof(Response));
    bzero(&cgi, sizeof(CGI));
    header.clear();
    body.clear();
    line.clear();
    http.clear();
    httpVersion.clear();
    methode.clear();
    URI.clear();
    Query.clear();
    RequestPath.clear();
    ResponseHeaders.clear();
    ResponseBody.clear();
    Boundry.clear();
    BoundryStart.clear();
    BoundryEnd.clear();
    Extension.clear();
    statusCode = 200;
    HeaderData.clear();
    index = 0;
    locationIndex = 0;
    IsDirectory = 0;
    ServerIndex = 1;
    SendFile = 0;
    FileSize = 0;
    offset = 0;
    RequestIsDone = false;
    CheckExtension = false;
    KeepAlive = false;
    isBoundry = false;
    isChuncked = false;
    BoundryVec.clear();
    CgiIsDone = false;
}

std::string     Request::InitRequest(std::string str, int fd, int in, Parsing &ps)
{
    Reset();
    Server = ps;
    (void)fd;

    // std::cout << "index---->" << ServerIndex << std::endl;

    ServerIndex = in;
    this->getRequest(str);
    GenerateResponse();
    std::cout << "StatusCode: " << statusCode << std::endl;
    std::string ret = ResponseHeaders + ResponseBody;
    RequestIsDone = true;
    return(ret);
}
