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
		return(statusCode = 404, 1);

	std::cout << "RequestPath IS: " << RequestPath << std::endl;

	if(IsDirectory == true && (URI[URI.size() - 1] != '/'))
		return(statusCode = 409, 1);

	if(IsDirectory == true && RequestPath == Loc.root)
		return(statusCode = 403, 1);
    if(IsDirectory)
	{
		if(DeleteDir())
			return(1);
	}
	else
	{
		if(DeleteFile())
			return(1);
	}
	return(0);
}

int		Request::DeleteFile()
{
	if(Loc.CheckCGI)
	{
		FillCgi();
		Rawr r = Server.CgiResult(cgi);
		ResponseBody =  r.body;
		statusCode = std::atoi(r.code.c_str());
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

int Request::CheckDirectoryFiles(std::string& directory, std::vector<std::string>& filesToDelete)
{
	DIR* dir;
	struct dirent* entry;

	dir = opendir(directory.c_str());
	if (dir == NULL)
		return (statusCode = 403, std::cout << "Failed to open directory." << std::endl, 1);

	std::string path;
	while ((entry = readdir(dir)) != NULL)
	{
		std::string str = entry->d_name;
		if (str == "." || str == ".." || str[0] == '.')
			continue;
		path = directory + str;
		if (isDirectory(path))
		{
			path += "/";
			if (CheckDirectoryFiles(path, filesToDelete) != 0)
				return (closedir(dir),1);
			else
				filesToDelete.push_back(path);
		}
		else
			filesToDelete.push_back(path);
	}
	closedir(dir);
	return 0;
}

int Request::DeleteDir()
{
	if (Loc.CheckCGI)
	{
		if (Loc.CheckIndex)
		{
			RequestPath = Loc.root + Loc.index;
			if (isFile(RequestPath, false))
			{
				FillCgi();
				Rawr r = Server.CgiResult(cgi);
				ResponseBody =  r.body;
				statusCode = std::atoi(r.code.c_str());
			}
			else
				return (statusCode = 403, 1);
		}
		else
			return (statusCode = 403, 1);
	}
	else
	{
		std::vector<std::string> filesToDelete;
		if (CheckDirectoryFiles(RequestPath, filesToDelete) != 0)
			return 1;

		std::cout << "filesToDelete.size(): " << filesToDelete.size() << std::endl;

		bool hasWriteAccess = true;
		for (size_t i = 0; i < filesToDelete.size(); i++)
		{
			std::cout << "file1: " << filesToDelete[i] << std::endl;
			if (access(filesToDelete[i].c_str(), W_OK) != 0)
			{
				hasWriteAccess = false;
				break;
			}
		}

		if (hasWriteAccess)
		{
			for (size_t i = 0; i < filesToDelete.size(); i++)
				if(remove(filesToDelete[i].c_str()) == -1)
					return (std::cout << "failed to delete: " << filesToDelete[i] << std::endl, statusCode = 501, 1);
			remove(RequestPath.c_str());
		}
		else
			return (statusCode = 403, std::cout << "Not deleting files due to lack of write access." << std::endl, 1);
	}
	return (statusCode = 204, 1);
}
