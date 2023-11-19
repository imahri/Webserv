#include "../../../includes/Request.hpp"

std::string    GetStatusCode(int index)
{
    switch (index)
    {
        case 100:
            return ( "Continue" );
        case 101:     
            return ( "Switching Protocol" );
        case 102:
            return ( "Processing" );
        case 103:
            return ( "Early Hints" );
        case 200:
            return (  "OK" );
        case 201:
            return (  "Created" );
        case 202:
            return (  "Accepted" );
        case 203:
            return (  "Non-Authoritative Information" );
        case 204:
            return (  "No Content" );
        case 205:
            return (  "Reset Content" );
        case 300:
            return ( "Multiple Choice" );
        case 301:
            return ( "Moved Permanently" );
        case 302:
            return ( "Found" );
        case 303:
            return ( "See Other" );
        case 304:
            return ( "Not Modified" );
        case 500:
            return ( "Internal Server Error" );
        case 501:
            return ( "Not Implemented" );
        case 502:
            return ( "Bad Gateway" );
        case 503:
            return ( "Service Unavailable" );
        case 504:
            return ( "Gateway Timeout" );
        case 505:
            return ( "HTTP Version Not Supported" );
        case 508:
            return ( "Loop Detected" );
        case 510:
            return ( "Not Extended" );
        case 511:
            return ( "Network Authentication Required" );
        case 400:
            return ( "Bad Request" );
        case 401:
            return ( "Unauthorized" );
        case 403:
            return ( "Forbidden" );
        case 404:
            return ( "Not Found" );
        case 405:
            return ( "Method Not Allowed" );
        case 406:
            return ( "Not Acceptable" );
        case 407:
            return ( "Proxy Authentication Required" );
        case 409:
            return ( "Conflict" );
        case 410:
            return ( "Gone" );
        case 411:
            return ( "Length Required" );
        case 412:
            return ( "Precondition Failed" );
        case 413:
            return ( "Payload Too Large" );
        case 414:
            return ( "URI Too Long" );
        case 415:
            return ( "Unsupported Media Type" );
        case 416:
            return ( "Requested Range Not Satisfiable" );
        case 418:
            return ( "I'm a teapot" );
        case 422:
            return ( "Unprocessable Entity" );
        case 451:
            return ( "Unavailable For Legal Reasons" );
        default:
            return ( "NOT FOUND" );
    }
    return 0;
}

std::string intToString(int number)
{
    std::ostringstream oss;
    oss << number;
    return oss.str();
}

int     Request::GenerateResponse()
{
    ResponseHeaders = "HTTP/1.1 " + intToString(statusCode) + " " + GetStatusCode(statusCode) + "\r\n";

    std::time_t currentTime = std::time(0);
    std::string str = (std::ctime(&currentTime));
    ResponseHeaders += "Date: " + str + " GMT\r\n";

    ResponseHeaders += "Content-Type: text/html\r\n";

    if(statusCode >= 400 && statusCode <= 600)
    {
        // ResponseHeaders = + ;
    }
    else if(statusCode >= 0 && statusCode < 400)
    {
        if(Req.ContentLength.size())
            ResponseHeaders += "Content-Lenght: " + Req.ContentLength + "\r\n";
    }
    ResponseHeaders += "\r\n";
    return(0);
}


//"<a class=\"icon dir\" href=\"" + it->second + "\">" + "Redirect to" + it->second + "</a><br>";
// ResponseBody += "<meta http-equiv=\"Refresh\" content=\"0; url='" + it->second + "'\" />";