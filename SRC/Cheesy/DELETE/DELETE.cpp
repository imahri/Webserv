#include "../../../includes/Request.hpp"

int		Request::DELETE()
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

	std::cout << "RequestPath IS: " << RequestPath << std::endl;

	if(IsDirectory == true && (URI[URI.size() - 1] != '/'))
		return(statusCode = 409, 1);

    if(IsDirectory)
	{
		puts("diririririri");
		if(DeleteDir())
			return(1);
	}
	else
	{
		puts("filefilefilefile");
		File = URI;
		if(DeleteFile())
			return(1);
	}
	return(0);
}

int		Request::CheckDirectoryFiles(std::string &directory)
{
	DIR 			*dir;
	struct dirent 	*entry;

	dir = opendir(directory.c_str());
	if (dir == NULL)
		return (statusCode = 404, std::cout << "Failed to open directory." << std::endl, 1);

	std::string path;
	while ((entry = readdir(dir)) != NULL)
	{
		std::string str = entry->d_name;
		std::cout << "str: " << str << std::endl;
		if(str != "." || str != "..")
		{
			path = directory + str;
			if(isDirectory(path))
				path += "/";
			std::cout << path << std::endl;
		}
	}
	closedir(dir);
	return(0);
}

int		Request::DeleteDir()
{
	if(Loc.CheckCGI)
	{
		if(Loc.CheckIndex)
		{
			RequestPath = Loc.root + Loc.index;
			if(isFile(RequestPath, false))
			{
				FillCgi();
				ResponseBody =  Server.CgiResult(cgi);
			}
			else
				return(statusCode = 403, 1);
		}
		else
			return(statusCode = 403, 1);
	}
	else
	{
		if(CheckDirectoryFiles(RequestPath))
			return(1);
		else
			return(statusCode = 204, 1);
	}
	return(0);
}

int		Request::DeleteFile()
{
	if(Loc.CheckCGI)
	{
		FillCgi();
		ResponseBody =  Server.CgiResult(cgi);
	}
	else
	{
		if(remove(RequestPath.c_str()) == -1)
			return(statusCode = 401, 1);
		else
			return(statusCode = 204, 1);
	}
	return(0);
}