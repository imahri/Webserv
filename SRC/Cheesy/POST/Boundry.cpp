#include "../../../includes/Request.hpp"


int		Request::parseChuncked()
{
// 	std::cout << "-----------------------HEADER CHUNCKED-------------------" << std::endl;
// 	std::cout << header << std::endl;
// 	std::cout << "-----------------------BODY-------------------" << std::endl;
// 	std::cout << body << std::endl;
	return(0);
}

int		Request::GetNextBoundry(std::string &base, bool check)
{
	size_t find = base.find("\r\n");
	if(find == base.npos)
		return(1);

	std::string ContentDisposition = base.substr(0, find);
	find = base.find("\r\n", find + 4);
	if(find == base.npos)
		return(1);

	std::string	FileName;
	std::string newStr;

	if(!check)
		newStr = base.substr(find + 4, base.length());
	else
		newStr = base.substr(find + 4, base.length() - BoundryEnd.length() - find - 6);
	

	std::vector<std::string> vec = Divide(ContentDisposition, ";");
	if(vec.size() != 3)
		return(1);

	for (size_t i = 0; i < vec.size(); i++)
	{
		if(i == 2)
		{
			find = vec[i].find("filename=\"");
			if(find != vec[i].npos)
			{
				FileName = vec[i].substr(find + 10, vec[i].length() - find - 11);
				if(FileName.length() == 0)
					return(1);
			}
		}
	}

	std::string path = Loc.upload_dir + FileName;
	std::ofstream file(path, std::ios::binary);
	if(!file)
		return(std::cout << "Can't create file" << std::endl, 2);
	// std::cout << "FILESIZE: " << newStr.length() << std::endl;
	file << newStr;
	return(0);
}

int Request::parseBoundry()
{
    // std::cout << "-----------------------HEADER BOUNDARY-------------------" << std::endl;
    // std::cout << header << std::endl;
    // std::cout << "-----------------------BODY-------------------" << std::endl;
    // std::cout << body << std::endl;
    // std::cout << "-----------------------END OF BODY-------------------" << std::endl;

    size_t find = Req.ContentType.find("boundary=");
    if (find == std::string::npos)
        return 1;

    Boundry = Req.ContentType.substr(find + 9);
    if (Boundry.empty())
        return 1;

    BoundryStart = "--" + Boundry;
    BoundryEnd = BoundryStart + "--";


    std::cout << "-----------------------START OF CHUNKS-------------------" << std::endl;
	std::string Fakebody = body;
	std::string str =  BoundryStart + "\r\n";
	BoundryVec = Divide(body, str);

	for (size_t i = 0; i < BoundryVec.size(); i++)
	{
		if(BoundryVec[i].size() != 0 || checkWhiteSpace(BoundryVec[i]) == 1)
		{
			if(i == BoundryVec.size() - 1)
			{
				if(GetNextBoundry(BoundryVec[i], true))
					return(1);
			}
			else
			{
				if(GetNextBoundry(BoundryVec[i], false))
					return(1);
			}
		}
	}
    std::cout << "-----------------------END OF CHUNKS-------------------" << std::endl;
    return 0;
}
