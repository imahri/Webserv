#include "../../../includes/Request.hpp"

int		Request::parseChuncked()
{
    std::string NewBody;
    size_t  end = body.find("0\r\n");
    if(end == body.npos)
        return 1;

    for (size_t i = 0; i < end; i++)
    {
        size_t  find = body.find("\r\n");
        if(find == body.npos)
            return 1;

        std::string str = body.substr(i, find);
        if(str.length() == 0)
            return(1);

        size_t count = CovertHexaToDecimal(str);
        if(count  == 0)
            return(2);

        size_t j = find + 2;
        
        for (; j < (count + find + 2); j++)
            NewBody += body[j];

        i += j + 4;
    }
    
    std::cout << "-------aaaaffff-------" << std::endl;
    std::cout << NewBody << std::endl;
    std::cout << "-------weeeeeee-------" << std::endl;
	return(0);
}
