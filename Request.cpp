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

int		Request::checkFirstLine(std::string check)
{
	(void)check;
	return(0);
}

int     Request::parseRequest(std::string buffer)
{
	std::cout << "----------------start------------------------" << std::endl;
	std::string line;

	std::vector<std::string> vecHeader = ft_split(buffer, "\r\n");
	std::vector<std::string>::iterator itVec = vecHeader.begin();
	for (; itVec != vecHeader.end(); itVec++)
	{
		std::cout << "|" <<  *itVec << "|" << std::endl;
	}
	
    // std::istringstream iss(buffer);

	// line = getNextToken(iss);
	// while (line.length())
	// {
	// 	std::cout << "|" <<  line << "|" << std::endl;
	// 	line = getNextToken(iss);
	// }
	std::cout << "---------------end---------------------------" << std::endl;
    return (0);
}
