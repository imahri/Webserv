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

std::string& ft_trim(std::string& s, std::string delimiter)
{
	size_t i = 0;
	while (i < s.size() && delimiter.find(s[i]) != std::string::npos) 
		s.erase(i, 1);

	i = s.size() - 1;

	while (i >= 0 && delimiter.find(s[i]) != std::string::npos) 
	{
		s.erase(i, 1);
		i--; 
	}

	return s;
}

unsigned long long Request::convertToBytes(const std::string& sizeString)
{
    std::string numberString;
    std::string unitString;

    // Separate the number and unit parts of the string
    for (std::size_t i = 0; i < sizeString.length(); ++i)
    {
        char ch = sizeString[i];
        if (std::isdigit(ch))
            numberString += ch;
        else
            unitString += ch;
    }

    // Convert the number part to an integer
    unsigned long long size = std::strtoull(numberString.c_str(), NULL, 10);

    // Convert the unit part to lowercase for easier comparison
    for (std::size_t i = 0; i < unitString.length(); ++i)
    {
        char &ch = unitString[i];
        ch = std::tolower(ch);
    }

    // Convert the size to bytes based on the specified unit
    if (unitString == "gb" || unitString == "gigabytes")
        size *= 1024ULL * 1024 * 1024;
    else if (unitString == "mb" || unitString == "megabytes")
        size *= 1024ULL * 1024;
    else if (unitString == "kb" || unitString == "kilobytes")
        size *= 1024ULL;

    return size;
}
