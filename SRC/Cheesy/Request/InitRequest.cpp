#include "../../../includes/Request.hpp"

void    Request::Reset()
{
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
    Extension.clear();
    Boundry.clear();
    BoundryStart.clear();
    BoundryEnd.clear();
    HeaderData.clear();
    BoundryVec.clear();
    index = 0;
    statusCode = 0;
    locationIndex = 0;
    IsDirectory = 0;
    ServerIndex = 0;
    SendFile = 0;
    FileSize = 0;
    offset = 0;
    CheckExtension = 0;
    CgiIsDone = 0;
    isBoundry = 0;
    isChuncked = 0;
    KeepAlive = 0;
    RequestIsDone = 0;
    //----------------location----------------//
    Loc.autoindex = 0;
    Loc.CheckIndex = 0;
    Loc.CheckCGI = 0;
    Loc.CheckRedirect = 0;
    Loc.CheckMethods = 0;
    Loc.CheckUploadDir = 0;
    Loc.CheckErrorPage = 0;
    Loc.client_body_max_size = 0;
    Loc.upload_dir.clear();
    Loc.root.clear();
    Loc.index.clear();
    Loc.methodes.clear();
    Loc.cgi.clear();
    Loc.redirect.clear();
    Loc.error_page.clear();
    //----------------cgi----------------//
    cgi.HeaderData.clear();
    cgi.header.clear();
    cgi.body.clear();
    cgi.httpVersion.clear();
    cgi.methode.clear();
    cgi.URI.clear();
    cgi.RequestPath.clear();
    cgi.Query.clear();
    cgi.root.clear();
    cgi.CodeStatus = 0;
    cgi.locationData.autoindex = 0;
    cgi.locationData.CheckIndex = 0;
    cgi.locationData.CheckCGI = 0;
    cgi.locationData.CheckRedirect = 0;
    cgi.locationData.CheckMethods = 0;
    cgi.locationData.CheckUploadDir = 0;
    cgi.locationData.CheckErrorPage = 0;
    cgi.locationData.client_body_max_size = 0;
    cgi.locationData.upload_dir.clear();
    cgi.locationData.root.clear();
    cgi.locationData.index.clear();
    cgi.locationData.methodes.clear();
    cgi.locationData.cgi.clear();
    cgi.locationData.redirect.clear();
    cgi.locationData.error_page.clear();
    cgi.ret.code.clear();
    cgi.ret.header.clear();
    cgi.ret.body.clear();
    cgi.ret.mapap.clear();

    //----------------Response----------------//
    Req.Host.clear();
    Req.Connection.clear();
    Req.UserAgent.clear();
    Req.ContentType.clear();
    Req.MimeType.clear();
    Req.ContentLength.clear();
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
