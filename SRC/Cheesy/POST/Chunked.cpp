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
// 	file << NewBody;

// 	return(0);
// }


//----------------------test//////////////////////////


int Request::parseChuncked()
{
    std::string NewBody;
    size_t end = body.find("\r\0\r\n");
    if (end == body.npos)
        return (puts("hnanan1"), 1);

    for (size_t i = 0; i < end;)
    {
        size_t find = body.find("\r\n", i);
        if (find == body.npos)
            return (puts("hnanan2"), 1);

        std::string str = body.substr(i, find - i);
        if (str.length() == 0)
            return (puts("hnanan3"), 1);

        size_t count = CovertHexaToDecimal(str);
        if (count == 0)
            break;

        size_t j = find + 2;

        for (; j < (count + find + 2); j++)
            NewBody += body[j];

        i = j + 4;
    }

    if (GetReverseMimeType() == 0)
        return (puts("hnanan5"), 1);

    std::string path = Loc.upload_dir + "yyy." + Req.MimeType;
    std::ofstream file(path, std::ios::binary);
    if (!file)
        return (std::cout << "Can't create file" << std::endl, 2);
    file.write(NewBody.data(), NewBody.size());

    return 0;
}