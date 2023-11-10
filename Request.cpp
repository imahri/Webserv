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

#include "Request.hpp"

int     Request::fillHeaderAndBody(std::string buffer)
{
	std::cout << "----------------start------------------------" << std::endl;

	index = buffer.find('\n');
	http = buffer.substr(0, index - 1);
	std::cout << "Http|" <<  http << "|" << std::endl;

	size_t oldIndex = index + 1;

	index = buffer.find("\r\n\r\n");
	for (; oldIndex < index; oldIndex++)
		header += buffer[oldIndex];

	for (oldIndex = index; oldIndex < buffer.size(); oldIndex++)
		body += buffer[oldIndex];
	
	std::cout << "header:|" << header << "|\n" << std::endl;
	// std::cout << "body|" << body << std::endl;
	std::cout << "---------------end---------------------------" << std::endl;

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

int		Request::checkHeader()
{
	std::vector<std::string> vec = ft_split(header, "\n\r");

	for (std::vector<std::string>::iterator it = vec.begin();  it != vec.end(); it++)
	{
		std::vector<std::string> vec = ft_split(*it, ':');
		HeaderData[ft_trim(vec[0], ' ')] = ft_trim(vec[1], ' ');
	}

	std::map<std::string, std::string>::iterator itM = HeaderData.begin();
	// for (; itM != HeaderData.end(); itM++)
	// 	std::cout << "f|" << itM->first << "|s|" << itM->second << "|" << std::endl;
	
	return(0);
}

int		Request::getRequest(std::string buffer)
{
	if(fillHeaderAndBody(buffer))
		return(1);
	if(parseRequest())
		return(1);
	return(0);
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

	return(0);
}
  