#include "../../../includes/Request.hpp"

int     Request::PostFile()
{
    int f = this->cgi.callCGI(this->Loc, RequestPath);
    if(Loc.CheckCGI && f != -1)
    {
        FillCgi();
        Rawr r = Server.CgiResult(cgi);
        statusCode = std::atoi(r.code.c_str());
        if(statusCode == 200)
        {
            ResponseBody =  r.body;
            ResponseHeaders = "HTTP/1.1 " + intToString(statusCode) + " " + GetStatusCode(statusCode) + "\r\n";
            std::time_t currentTime = std::time(0);
            std::string str = (std::ctime(&currentTime));
            ResponseHeaders += "Date: " + str.substr(0, str.size() - 1) + " GMT\r\n";
            ResponseHeaders += r.header;
            CgiIsDone = true;
        }
        else
            return(1);
    }
    else
        return(statusCode = 403, 1);

    return(0);
}

int     Request::PostDir()
{
    ResponseBody.clear();
    std::string filename = Loc.root + "index.html";
    if(isFile(filename, false))
        return(RequestPath = filename, PostFile());
    else if(Loc.CheckIndex)
    {
        filename = Loc.root + Loc.index;
        if(isFile(filename, false))
            return(RequestPath = filename, PostFile());
        else
            return(statusCode = 403, 1);
    }
    else
        return(statusCode = 403, 1);
    return(0);
}

int     Request::GetRessource()
{
    struct stat fileStat;

	size_t find = URI.find("/Users/");
	if(find != URI.npos)
		RequestPath = URI;
	else if(URI != "/")
		RequestPath = Loc.root + URI.substr(1, URI.size());
	else
		RequestPath = Loc.root;
	
	if (stat(RequestPath.c_str(), &fileStat) == 0)
	{
		if (S_ISDIR(fileStat.st_mode))
			IsDirectory = true;
		else if (S_ISREG(fileStat.st_mode))
			IsDirectory = false;
	}
	else
		return(statusCode = 404, 1);

    if(IsDirectory == true && (URI[URI.size() - 1] != '/'))
        return(GenerateRedirection(), statusCode = 301, 1);

    if(IsDirectory)
    {
        if(PostDir())
            return(1);
    }
    else
    {
        if(PostFile())
            return(1);
    }
    return(0);
}

int     Request::parseBody()
{
    std::string name = URI.substr(1, URI.size());
    if(name.length() == 0)
        return(statusCode = 400, 1);

    std::string filename = Loc.upload_dir + name;
    std::ofstream file(filename.c_str(), std::ios::out | std::ios::binary);
    if(file.is_open())
    {
        file << body;
        file.close();
    }
    else
        return(statusCode = 500, 1);
    return(0);
}

int		Request::POST()
{
    if(Loc.CheckUploadDir)
    {
        statusCode = 201;
        if(isBoundry == true)
        {
            if(parseBoundry())
                return 1;
        }
        else if(isChuncked == true)
        {
            if(parseChuncked())
                return 1;
        }
        else
        {
            if(parseBody())
                return 1;
        }
    }
    else
    {
        if(GetRessource())
            return (1);
    }
    return(0);
}
