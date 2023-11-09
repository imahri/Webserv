#include "Request.hpp"

Request::Request(){}

Request::Request(const Request &obj)
{
   *this = obj;
}

Request &Request::operator=(const Request &other)
{
    if (this != &other)
        return *this;
    return *this;
}

Request::~Request(){}

std::string Request::getNextToken(std::istringstream &iss)
{
    std::string token;

    std::getline(iss, token, '\n');
    return token;
}

int   Request::checkDigit(std::string str)
{
    for (size_t i = 0; i < str.length(); i++)
	{
		if(i != 0 && str[i] == '.' && i + 1 != str.length())
			continue;
		else
    	    if(!std::isdigit(str[i]))
	            return(1);
	}
    return(0);
}

int   Request::checkWhiteSpace(std::string str)
{
    for (size_t i = 0; i < str.length(); i++)
        if(!std::isspace(str[i]))
            return(1);
    return(0);
}

int   Request::checkNumbers(std::string str)
{
    for (size_t i = 0; i < str.length(); i++)
	{
		if(!std::isdigit(str[i]))
			return(1);
	}
    return(0);
}
