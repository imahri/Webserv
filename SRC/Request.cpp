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

#include "../includes/Request.hpp"

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

	if(methode != "POST" && methode != "GET" && methode != "DELETE")
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

int		Request::checkLocations()
{
	// std::vector < std::pair <std::string, std::string > > data = Server.getLocationSpecificDatas(1,1,"redirect");
	// for (size_t i = 0; i < data.size(); i++)
	// 	std::cout << data[i].first << "   " << data[i].second << std::endl;	std::cout << "11" << std::endl;


	std::vector < std::string> it = Server.getLocationSpecificData(1,1,"path");
	for (size_t i = 0; i < it.size(); i++)
		std::cout << "-->" << it[i]<< std::endl;


	// 	int		found = 0;
	
 	// for (std::vector<Location>::const_iterator it = locations.begin(); it != locations.end(); it++)
    // {
    //     const Location& location = *it;
	// 	if(location.path == URI)
	// 		found = 1;
    //     std::cout << std::endl;
    // }

	// if(found == 0)
	// 	return(statusCode = 404, 1);
	

	return(0);
}

int		Request::checkHeader()
{
	std::map<std::string, std::string>::iterator itM = HeaderData.begin();

	int transferEncoding = 0,contentLength = 0;
	for (; itM != HeaderData.end(); itM++)
	{
		if(itM->second.size() == 0)
			return(statusCode = 400, 1);

		if(itM->first == "Transfer-Encoding" && itM->second != "chunked")
			return(statusCode = 501, 1);

		if(itM->first == "Transfer-Encoding")
			transferEncoding = 1;

		if(itM->first == "Content-Length")
			contentLength = 1;
	}

	if(transferEncoding == 0 && contentLength == 0 && methode == "POST")
		return(statusCode = 400, 1);

	if(checkLocations())
		return(1);
	return(0);
}

int		Request::getRequest(std::string buffer)
{
	if(fillHeaderAndBody(buffer))
		return(std::cout << "BAD REQUEST" << std::endl,1);
	if(parseRequest())
		return(std::cout << "BAD REQUEST" << std::endl,1);
	std::cout << "GOOD REQUEST" << std::endl;
	return(0);
}

int		Request::GET()
{
	
	return(0);
}

int		Request::POST()
{

	return(0);
}

int		Request::DELETE()
{

	return(0)	;
}


int		Request::parseRequest()
{
	clientMaxBodySize = convertToBytes("3GB");

	if(checkHttp())
		return(1);
	if(checkHeader())
		return(1);
	if(checkBody())
		return(1);
	if(GET())
		return(1);
	if(POST())
		return(1);
	if(DELETE())
		return(1);
	return(0);
}
  