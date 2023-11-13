/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalParsing.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaqsi <ytaqsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:53:49 by ytaqsi            #+#    #+#             */
/*   Updated: 2023/11/13 15:57:50 by ytaqsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Request.hpp"

Webserv::Webserv()
{
	httpStatusCodes.push_back("100");
    httpStatusCodes.push_back("101");
    httpStatusCodes.push_back("102");

    // 2xx (Successful)
    httpStatusCodes.push_back("200");
    httpStatusCodes.push_back("201");
    httpStatusCodes.push_back("202");
    httpStatusCodes.push_back("203");
    httpStatusCodes.push_back("204");
    httpStatusCodes.push_back("205");
    httpStatusCodes.push_back("206");
    httpStatusCodes.push_back("207");
    httpStatusCodes.push_back("208");
    httpStatusCodes.push_back("226");

    // 3xx (Redirection)
    httpStatusCodes.push_back("300");
    httpStatusCodes.push_back("301");
    httpStatusCodes.push_back("302");
    httpStatusCodes.push_back("303");
    httpStatusCodes.push_back("304");
    httpStatusCodes.push_back("305");
    httpStatusCodes.push_back("307");
    httpStatusCodes.push_back("308");

    // 4xx (Client Errors)
    httpStatusCodes.push_back("400");
    httpStatusCodes.push_back("401");
    httpStatusCodes.push_back("402");
    httpStatusCodes.push_back("403");
    httpStatusCodes.push_back("404");
    httpStatusCodes.push_back("405");
    httpStatusCodes.push_back("406");
    httpStatusCodes.push_back("407");
    httpStatusCodes.push_back("408");
    httpStatusCodes.push_back("409");
    httpStatusCodes.push_back("410");
    httpStatusCodes.push_back("411");
    httpStatusCodes.push_back("412");
    httpStatusCodes.push_back("413");
    httpStatusCodes.push_back("414");
    httpStatusCodes.push_back("415");
    httpStatusCodes.push_back("416");
    httpStatusCodes.push_back("417");
    httpStatusCodes.push_back("418");
    httpStatusCodes.push_back("421");
    httpStatusCodes.push_back("422");
    httpStatusCodes.push_back("423");
    httpStatusCodes.push_back("424");
    httpStatusCodes.push_back("426");
    httpStatusCodes.push_back("428");
    httpStatusCodes.push_back("429");
    httpStatusCodes.push_back("431");
    httpStatusCodes.push_back("451");

    // 5xx (Server Errors)
    httpStatusCodes.push_back("500");
    httpStatusCodes.push_back("501");
    httpStatusCodes.push_back("502");
    httpStatusCodes.push_back("503");
    httpStatusCodes.push_back("504");
    httpStatusCodes.push_back("505");
    httpStatusCodes.push_back("506");
    httpStatusCodes.push_back("507");
    httpStatusCodes.push_back("508");
    httpStatusCodes.push_back("510");
    httpStatusCodes.push_back("511");
}

bool		Webserv::finalParsing()
{
	for (size_t i = 0; i < servers.size(); i++)
	{
		for (size_t j = 0; j < servers[i].size(); j++)
		{
			std::cout << servers[i][j] << std::endl;
		}
	}
	
	return true;
}
