#include "../../includes/Request.hpp"

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

std::string getNextToken(std::istringstream &iss)
{
    std::string token;

    std::getline(iss, token, '\n');
    return token;
}

int   checkDigit(std::string str)
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

int   checkWhiteSpace(std::string str)
{
    for (size_t i = 0; i < str.length(); i++)
        if(!std::isspace(str[i]))
            return(1);
    return(0);
}

int   checkNumbers(std::string str)
{
    for (size_t i = 0; i < str.length(); i++)
	{
		if(!std::isdigit(str[i]))
			return(1);
	}
    return(0);
}

std::vector<std::string> ft_split(std::string &s, std::string delimiter)
{
	std::vector<std::string> arr;
	std::string current;
	size_t size = s.size();

	for (size_t i = 0; i < size; i++) 
	{
		while (delimiter.find(s[i]) != std::string::npos)
			i++;
		while (i < size && delimiter.find(s[i]) == std::string::npos)
			current += s[i++];
		if (!current.empty()) 
		{
			arr.push_back(current);
			current.clear();
		}
	}
	return arr;
}

std::vector<std::string> ft_split(std::string& s, char c)
{
	std::vector<std::string> arr;
	std::string			line;
	std::istringstream	iss(s);
	
	while (std::getline(iss, line, c))
		arr.push_back(line);
	return arr;
}

std::vector<std::string> ft_split(std::string& s)
{
	std::vector<std::string> arr;
	std::string			line;
	std::istringstream	iss(s);
	
	while (iss >> line)
		arr.push_back(line);
	return arr;
}

std::string& ft_trim(std::string& s, char c)
{
	size_t i = 0;
	while (i < s.size() && s[i] == c) 
		s.erase(i, 1);

	i = s.size() - 1;
	if (i == std::string::npos)
		return s;
	while (i >= 0 && s[i] == c) 
	{
		s.erase(i, 1);
		i--; 
	}

	return s;
}

std::string ft_trim(std::string s, std::string delimiter)
{
	size_t i = 0;

    
    while (i < s.size() && delimiter.find(s[i]) != std::string::npos)
        s.erase(i, 1);

    i = s.size();
    while (i > 0 && delimiter.find(s[i - 1]) != std::string::npos)
    {
        i--;
        s.erase(i, 1);
    }

	return s;
}

size_t convertToCharacters(std::string sizeString)
{
    size_t size = std::atoi(sizeString.c_str());
    size_t factor = 1;

    if (sizeString.find("G") != std::string::npos)
        factor = 1024 * 1024 * 1024;
	else if (sizeString.find("MB") != std::string::npos)
        factor = 1024 * 1024;
	else if (sizeString.find("KB") != std::string::npos)
        factor = 1024;
    return (size * factor);
}
