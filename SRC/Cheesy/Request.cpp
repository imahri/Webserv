/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamghar <eamghar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 02:35:15 by eamghar           #+#    #+#             */
/*   Updated: 2023/09/25 13:46:52 by eamghar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Request.hpp"

int     Request::fillHeaderAndBody(std::string buffer)
{
	index = buffer.find('\n');
	http = buffer.substr(0, index - 1);

	size_t oldIndex = index + 1;

	index = buffer.find("\r\n\r\n");
	for (; oldIndex < index; oldIndex++)
		header += buffer[oldIndex];

	for (oldIndex = index; oldIndex < buffer.size(); oldIndex++)
		body += buffer[oldIndex];

	std::vector<std::string> vec = ft_split(header, "\n\r");
	for (std::vector<std::string>::iterator it = vec.begin();  it != vec.end(); it++)
	{
		std::vector<std::string> vec = ft_split(*it, ':');
		HeaderData[ft_trim(vec[0], ' ')] = ft_trim(vec[1], ' ');
	}
    return (0);
}

int		Request::checkHttp()
{
	std::string		search = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789-._~:/?#[]@!$&'()*+,;=%";
	size_t			find;

	std::vector<std::string> vec = ft_split(http, " \n\r\t");
	std::vector<std::string>::iterator it = vec.begin();

	if(vec.size() != 3)
		return(statusCode = 400, 1);
	
	it = vec.begin();
	methode = *it;
	URI = *(it + 1);
	httpVersion = *(it + 2);

	if((methode != "POST" && methode != "GET" && methode != "DELETE") || (httpVersion != "HTTP/1.1"))
		return(statusCode = 400, 1);
	else if(URI.size() > 2048)
		return(statusCode = 414, 1);

	for (size_t i = 0; i < URI.size(); i++)
		if((find = search.find(URI[i])) == search.npos)
			return(statusCode = 400, 1);

	return(0);
}

int		Request::checkBody()
{
	if(body.size() > clientMaxBodySize)
		return(statusCode = 413, 1);
	return(0);
}



int		Request::GetCorrectLocation()
{
	if(locationIndex == 0)
	{

	}
	return(0);
}

int		Request::checkLocations()
{
	int		uriFound = 0, methodeFound = 0;

	std::vector < std::pair <std::string, std::vector < std::string > > > locationData;
	for (size_t i = 1; i < Server.getLocationsNumber(1); i++)
	{
		locationData = Server.getLocationData(1, i);
		if(URI == locationData[0].second[0])
		{
			uriFound = 1;
			locationIndex = i;
		}
	}
	// if(uriFound == 0)
	// {
	// 	puts("here3");
	// 	return(statusCode = 404, 1);
	// }
	
	if(locationIndex != 0)//location found
	{
		std::vector < std::pair <std::string, std::string > > data = Server.getLocationMultiple(1, locationIndex, "redirect");
		for (size_t j = 0; j < data.size(); j++)
			return(statusCode = std::atoi(data[j].first.c_str()), 1);

		std::vector < std::string> it = Server.getLocationSingle(1, locationIndex, "methods");
		for (size_t i = 0; i < it.size(); i++)
			if(methode == it[i])
				methodeFound = 1;

		if(methodeFound == 0)
			return(statusCode = 405, 1);
	}
	//location not found so iam going to use the server's stuff
	return(0);
}

int		Request::parseChuncked()
{
	
	std::cout << "-----------------------HEADER-------------------" << std::endl;
	std::cout << header << std::endl;
	std::cout << "-----------------------BODY-------------------" << std::endl;
	std::cout << body << std::endl;
	return(0);
}

int		Request::checkHeader()
{
	std::map<std::string, std::string>::iterator itM = HeaderData.begin();

	bool isChuncked = false;
	int transferEncoding = 0, contentLength = 0;
	for (; itM != HeaderData.end(); itM++)
	{
		if(itM->second.size() == 0)
			return(statusCode = 400, 1);

		if(itM->first == "Transfer-Encoding" && itM->second != "chunked")
			return(statusCode = 501, 1);

		if(itM->first == "Transfer-Encoding" && itM->second == "chunked")
			isChuncked = true;

		if(itM->first == "Transfer-Encoding")
			transferEncoding = 1;

		if(itM->first == "Content-Length")
			contentLength = 1;
	}

	if(transferEncoding == 0 && contentLength == 0 && methode == "POST")
		return(statusCode = 400, 1);

	if(isChuncked == true)
		parseChuncked();

	if(checkLocations())
		return(1);
	return(0);
}

int		Request::getRequest(std::string buffer)
{
	if(fillHeaderAndBody(buffer))
		return(std::cout << "CAUGHT REQUEST" << std::endl,1);
	if(parseRequest())
		return(std::cout << "CAUGHT REQUEST" << std::endl,1);
	std::cout << "GOOD REQUEST" << std::endl;
	return(0);
}

int		Request::DELETE()
{
	
	return(0)	;
}

int		Request::parseRequest()
{
	clientMaxBodySize = convertToBytes("3GB");
	locationIndex = 0;
	directory = -1;

	if(checkHttp())
		return(1);
	if(checkHeader())
		return(1);
	if(checkBody())
		return(1);
	if(methode == "GET")
	{
		if(GET())
			return(1);
	}
	else if(methode == "POST")
	{
		if(POST())
			return(1);
	}
	else if(DELETE())
		return(1);

	return(0);
}
  