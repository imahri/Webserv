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

    const int bufferSize = 50000;
    char buffer[bufferSize];

    Tostore.clear();

    while (fileStream.read(buffer, bufferSize))
        Tostore.append(buffer, bufferSize);
    Tostore.append(buffer, fileStream.gcount());

    fileStream.close();
    return 0;
}

int Request::FillResponseBodyFromFile()
{
    std::ifstream fileStream(RequestPath, std::ios::binary);
    if (!fileStream)
        return (std::cerr << "Error: Unable to open the file " << RequestPath << std::endl, statusCode = 403, 1);

    fileStream.seekg(0, fileStream.beg);

    const int bufferSize = 50000;
    char buffer[bufferSize];

    ResponseBody.clear();

    while (fileStream.read(buffer, bufferSize))
	{
        ResponseBody.append(buffer, bufferSize);
		bzero(buffer, bufferSize);
	}

    ResponseBody.append(buffer, fileStream.gcount());

    ResponseBody += "\r\n";

    fileStream.close();
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
	this->cgi.root = Loc.root;

	this->cgi.locationData.autoindex = this->Loc.autoindex;
	this->cgi.locationData.CheckIndex = this->Loc.CheckIndex;
	this->cgi.locationData.CheckCGI = this->Loc.CheckCGI;
	this->cgi.locationData.CheckRedirect = this->Loc.CheckRedirect;
	this->cgi.locationData.CheckMethods = this->Loc.CheckMethods;
	this->cgi.locationData.CheckUploadDir = this->Loc.CheckUploadDir;
	this->cgi.locationData.upload_dir = this->Loc.upload_dir;
	this->cgi.locationData.root = this->Loc.root;
	this->cgi.locationData.index = this->Loc.index;
	this->cgi.locationData.methodes = this->Loc.methodes;
	this->cgi.locationData.client_body_max_size = this->Loc.client_body_max_size;
	this->cgi.locationData.cgi = this->Loc.cgi;
	this->cgi.locationData.redirect = this->Loc.redirect;
};

int		Request::GetFileLength(std::string &fileName)
{
	struct stat fileStat;

	if (stat(fileName.c_str(), &fileStat) == 0)
	{
		FileSize = fileStat.st_size;
		if(FileSize > 10000000)
			return(1);
		return(0);
	}
	return(0);
}

int		Request::GetFile()
{
	if(locationIndex == 0)
		return(1);
	else
	{
		// std::cout << "======================================================>>>" << this->cgi.callCGI(this->Loc, this->RequestPath) << std::endl;
		int f = this->cgi.callCGI(this->Loc, this->RequestPath);
		if(Loc.CheckCGI && f != -1)
		{
			FillCgi();
			Rawr r = Server.CgiResult(cgi);
			statusCode = std::atoi(r.code.c_str());
			if(statusCode == 200)
			{
				std::cout << "---------------------------CGI---------------------" << std::endl;
				ResponseBody =  r.body;
				ResponseHeaders = "HTTP/1.1 " + intToString(statusCode) + " " + GetStatusCode(statusCode) + "\r\n";
				std::time_t currentTime = std::time(0);
				std::string str = (std::ctime(&currentTime));
				ResponseHeaders += "Date: " + str.substr(0, str.size() - 1) + " GMT\r\n";
				ResponseHeaders += r.header;
				std::cout << ResponseHeaders << std::endl;
				CgiIsDone = true;
				std::cout << "---------------------------END OF CGI---------------------" << std::endl;
			}
			else
				return(1);
		}
		else
		{
			if(GetFileLength(RequestPath))
				return(SendFile = true, statusCode = 200, 1);
			else if(FillResponseBodyFromFile())
				return(1);
		}
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
		ResponseBody = "<h1>" + RequestPath + "</h1>";
		while ((entry = readdir(dir)) != NULL)
		{
			link = RequestPath + entry->d_name;
			if(isDirectory(link))
				link += "/";
			ResponseBody += "<a class=\"icon dir\" href=\"" + link + "\">" + entry->d_name + "</a><br>";
		}
		ResponseBody += "\r\n";
		closedir(dir);
	}
	else
	{
		ResponseBody.clear();
		std::string filename = Loc.root + URI  + "index.html";
		if(isFile(filename, false))
			return(RequestPath = filename, GetFile());
		else if(isFile(Loc.root + "index.html", false))
			return(RequestPath = Loc.root + "index.html", GetFile());
		else if(Loc.CheckIndex)
		{
			filename = Loc.root + URI + Loc.index;
			if(isFile(filename, false))
				return(RequestPath = filename, GetFile());
			else if(isFile(Loc.root + Loc.index, false))
				return(RequestPath = Loc.root + Loc.index, GetFile());
			else
				return(statusCode = 403, 1);
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
		return(statusCode = 404, 1);

	if(IsDirectory == true && (URI[URI.size() - 1] != '/'))
		return(GenerateRedirection(), statusCode = 301, 1);
	else if(IsDirectory == false && CheckExtension == false)
		return(statusCode = 415, 1);
	else

	if(IsDirectory)
	{
		if(GetDirectory())
			return(1);
	}
	else
	{
		if(GetFile())
			return(1);
	}
	return(0);
}
