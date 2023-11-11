/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaqsi <ytaqsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:12:54 by ytaqsi            #+#    #+#             */
/*   Updated: 2023/11/11 11:31:26 by ytaqsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/webserv.hpp"

int main(int ac, char **av)
{
	Webserv webServ;
	webServ.parsing(ac, av);
	webServ.fillServerList();

	// // std::cout << webServ.getLocationsNumber(0) << std::endl;


	std::vector < std::pair <std::string, std::vector < std::string > > > locationData = webServ.getLocationData(1, 1);
	for (std::vector<std::pair<std::string, std::vector<std::string> > >::iterator it = locationData.begin(); it != locationData.end(); ++it)
	{
		std::cout << it->first << std::endl;
		for (std::vector<std::string>::iterator innerIt = it->second.begin(); innerIt != it->second.end(); ++innerIt) 
		{
			std::cout << *innerIt << " ";
		}
		std::cout << std::endl;
		std::cout << "--------------------------" <<std::endl;
	}

	
	// std::vector < std::pair <std::string, std::vector < std::string > > > serverData = webServ.serverData(1);
	// for (std::vector<std::pair<std::string, std::vector<std::string> > >::iterator it = serverData.begin(); it != serverData.end(); ++it)
	// {
	// 	std::cout << it->first << std::endl;
	// 	for (std::vector<std::string>::iterator innerIt = it->second.begin(); innerIt != it->second.end(); ++innerIt) 
	// 	{
	// 		std::cout << *innerIt << " ";
	// 	}
	// 	std::cout << std::endl;
	// 	std::cout << "--------------------------" <<std::endl;
	// }
	
	
	
	// std::vector < std::pair <std::string, std::string > > erroPages = webServ.getServerErrorPages(1);
	// for (std::vector < std::pair <std::string, std::string > >::iterator it = erroPages.begin(); it != erroPages.end(); ++it)
	// {
	// 	std::cout << it->first << " " << it->second << std::endl;
	// 	std::cout << "--------------------------" <<std::endl;
	// }
	

	
}

