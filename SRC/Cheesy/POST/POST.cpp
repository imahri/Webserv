#include "../../../includes/Request.hpp"

int     Request::PostFile()
{
    if(Loc.CheckCGI)
    {
        FillCgi();
        ResponseBody =  Server.CgiResult(cgi).body;
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
		return(puts("hehrhherehrehrehr"), statusCode = 404, 1);

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

int		Request::POST()
{
    if(Loc.CheckUploadDir)
    {
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
        statusCode = 201;
    }
    else
    {
        if(GetRessource())
            return (1);
    }
	return(0);
}
