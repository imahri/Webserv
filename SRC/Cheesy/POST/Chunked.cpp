#include "../../../includes/Request.hpp"

int     Request::GetReverseMimeType()
{
    std::map < std::string, std::vector < std::string > >::iterator it = Server.responseTypes.begin();
	for (; it != Server.responseTypes.end(); it++)
	{
        if(Req.ContentType == it->first)
            return(Req.MimeType = it->second[0], 1);
	}
    return(0);
}

// int		Request::parseChuncked()
// {
//     std::string NewBody;
//     size_t  end = body.find("0\r\n");
//     if(end == body.npos)
//         return 1;

//     for (size_t i = 0; i < end; i++)
//     {
//         size_t  find = body.find("\r\n");
//         if(find == body.npos)
//             return 1;

//         std::string str = body.substr(i, find);
//         if(str.length() == 0)
//             return(1);

//         size_t count = CovertHexaToDecimal(str);
//         if(count  == 0)
//             return(2);

//         size_t j = find + 2;
        
//         for (; j < (count + find + 2); j++)
//             NewBody += body[j];

//         i += j + 4;
//     }

//     if(GetReverseMimeType() == 0)
//         return(1);


//     std::string path = Loc.upload_dir + "yyy." + Req.MimeType;
// 	std::ofstream file(path, std::ios::binary);
// 	if(!file)
// 		return(std::cout << "Can't create file" << std::endl, 2);
//     std::cout << "size: " << NewBody.length() << std::endl;
// 	file << NewBody;

// 	return(0);
// }


int     Request::parseChuncked()
{
    std::cout << "-----------------------------" << std::endl;
    std::string requestBody = body;
    std::istringstream iss(requestBody);
    std::ostringstream oss;
    
    std::string line;
    while (std::getline(iss, line))
    {
        if (line.empty())
            break;

        size_t semicolonPos = line.find(';');
        if (semicolonPos != std::string::npos)
            line = line.substr(0, semicolonPos);

        size_t chunkSize = CovertHexaToDecimal(line);

        std::string chunkData(chunkSize, '\0');
        iss.read(&chunkData[0], chunkSize);
        oss << chunkData;

        std::getline(iss, line);
    }

    if(GetReverseMimeType() == 0)
        return(1);

    std::string path = Loc.upload_dir + "yyy." + Req.MimeType;
    std::ofstream file(path, std::ios::binary);
    if(!file)
        return(std::cout << "Can't create file" << std::endl, 2);
    std::string str =  oss.str();
    std::cout << "size: " << str.length() << std::endl;
    file << str;

    return (0);
}
