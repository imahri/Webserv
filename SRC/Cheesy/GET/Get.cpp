#include "../../../includes/Request.hpp"

int		readFile(std::string &fileName, std::string &Tostore)
{
	size_t		FileSize;

	std::ifstream fileStream(fileName, std::ios::binary);
    if (!fileStream)
        return (std::cerr << "Error: Unable to open the file " << fileName << std::endl, 1);

    fileStream.seekg(0, fileStream.end);
    FileSize = fileStream.tellg();
    fileStream.seekg(0, fileStream.beg);

    const int bufferSize = 4096;
    char buffer[bufferSize];

    Tostore.clear();

    while (fileStream.read(buffer, bufferSize))
        Tostore.append(buffer, bufferSize);
    Tostore.append(buffer, fileStream.gcount());

    std::cout << "FILE SIZE: " << FileSize << " BODY SIZE: " << Tostore.length() << std::endl;

    fileStream.close();
    return 0;
}


int Request::FillResponseBodyFromFile()
{
    std::ifstream fileStream(RequestPath, std::ios::binary);
    if (!fileStream)
    {
        std::cerr << "Error: Unable to open the file " << RequestPath << std::endl;
        statusCode = 404;
        return 1;
    }

    fileStream.seekg(0, fileStream.end);
    FileSize = fileStream.tellg();
    fileStream.seekg(0, fileStream.beg);

    const int bufferSize = 4096;
    char buffer[bufferSize];

    ResponseBody.clear();

    while (fileStream.read(buffer, bufferSize))
        ResponseBody.append(buffer, bufferSize);

    ResponseBody.append(buffer, fileStream.gcount());

    std::cout << "FILE SIZE: " << FileSize << " BODY SIZE: " << ResponseBody.length() << std::endl;

    ResponseBody += "\r\n";

    fileStream.close();

    SendFile = true;
    return 0;
}


void		Request::FillCgi()
{
	this->cgi.HeaderData = HeaderData;
	this->cgi.header = header;
	this->cgi.body = body;
	this->cgi.httpVersion = httpVersion;
	this->cgi.methode = methode;
	this->cgi.URI = URI;
	this->cgi.RequestPath = RequestPath;
	this->cgi.CodeStatus = statusCode;
	this->cgi.Query = Query;
	this->cgi.root = this->Loc.root;
};


int		Request::GetFile()
{
	if(locationIndex == 0)
		return(1);
	else
	{
		if(Loc.CheckCGI)
		{
			FillCgi();
			ResponseBody =  Server.CgiResult(cgi);
			//Run CGI on requested file
		}
		else if(FillResponseBodyFromFile())
			return(1);
	}
	return(0);
}

int		Request::GetDirectory()
{
	if(Loc.autoindex)
	{
		DIR 			*dir;
		struct dirent 	*entry;

		dir = opendir(RequestPath.c_str());
		if (dir == NULL)
			return (statusCode = 404, std::cout << "Failed to open directory." << std::endl, 1);

		std::string link;
		ResponseBody.clear();
		ResponseBody = "<h1>Name</h1>";
		while ((entry = readdir(dir)) != NULL)
		{
			link = RequestPath + entry->d_name;
			if(isDirectory(link))
				link += "/";
			std::cout << "LINK: " << link<< std::endl;
			ResponseBody += "<a class=\"icon dir\" href=\"" + link + "\">" + entry->d_name + "</a><br>";
		}
		ResponseBody += "\r\n";
		closedir(dir);
	}
	else
	{
		ResponseBody.clear();
		std::string filename = Loc.root + "index.html";
		if(isFile(filename, false))
			return(RequestPath = filename, GetFile());
		else if(Loc.CheckIndex)
		{
			filename = Loc.root + Loc.index;
			if(isFile(filename, false))
				return(RequestPath = filename, GetFile());
		}
		else
			return(statusCode = 403, 1);
	}
	return(0);
}

int		Request::GET()
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
		return(puts("hehrhherehrehrehr") ,statusCode = 404, 1);

	std::cout << "RequestPath IS: " << RequestPath << std::endl;

	std::cout << "CHECK: " << URI[URI.size() - 1] << std::endl;
	// if(IsDirectory == true && (URI[URI.size() - 1] != '/' || URI != "/"))
	// 	return(statusCode = 301, 1);

	if(IsDirectory)
	{
		if(GetDirectory())
			return(1);
	}
	else
	{
		File = URI;
		if(GetFile())
			return(1);
	}
	return(0);
}
