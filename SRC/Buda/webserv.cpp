/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaqsi <ytaqsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:25:18 by ytaqsi            #+#    #+#             */
/*   Updated: 2023/11/16 15:31:22 by ytaqsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Request.hpp"

Webserv::Webserv(const Webserv& copy) : servers(copy.servers), responseTypes(copy.responseTypes) {}

Webserv& Webserv::operator=(const Webserv& copy)
{
    if (this != &copy)
	{
        this->servers = copy.servers;
		this->responseTypes = copy.responseTypes;
	}
    return *this;
}

void		Webserv::fillResponseTypes()
{
	std::string		line;
	std::ifstream	typesFile;

	typesFile.open("SRC/Buda/types.txt");
	if (!typesFile)
	{
		std::cerr << "Unable to open the file types.txt" << std::endl;
		return ;
	}

	while (std::getline(typesFile, line))
	{
		std::vector < std::string >	splitedLine = ft_split(line, " ;");
		std::vector < std::string >	values(splitedLine.begin() + 1, splitedLine.end());
		
		if (line.empty() || ft_isAllSpace(line))
			continue;
		this->responseTypes[splitedLine[0]] = values;
		splitedLine.clear();
		values.clear();
	}

	// std::map < std::string, std::vector < std::string > >::iterator it = responseTypes.begin();
	// for (; it != responseTypes.end(); it++)
	// {
	// 	std::cout << "|" + it->first + "|" << std::endl;
	// 	for (size_t j = 0; j < it->second.size(); j++)
	// 	{
	// 		std::cout << "|" +it->second[j]+ "|" << " ";
	// 	}
	// 	std::cout << std::endl;
	// 	std::cout << "--------------------------------------------------" << std::endl;
	// }
	
}
