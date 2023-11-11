/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaqsi <ytaqsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:46:12 by ytaqsi            #+#    #+#             */
/*   Updated: 2023/11/11 17:47:30 by ytaqsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>
#include <string>
#include <sstream>

#include "Request.hpp"

// std::vector<std::string> ft_split(std::string &s, std::string delimiter);
// std::vector<std::string> ft_split(std::string &s, char c);
// std::vector<std::string> ft_split(std::string &s);

// std::string ft_trim(std::string s, std::string delimiter);
// std::string &ft_trim(std::string &s, char c);

bool ft_isAllSpace(std::string &s);

struct parsingStruct
{
	std::string name;
	bool open_bracket;
	bool close_bracket;
};

class Webserv
{
	private:
		std::vector < std::vector < std::string > > servers;
		std::ifstream configFile;
		std::string fileName;

	public:

		Webserv(){};
		Webserv(const Webserv& copy);
		Webserv&	operator = (const Webserv& copy);
		bool		parsing(int ac, char **av);
		void		fillServerList();


		int																		getServersNumber();
		int																		getLocationsNumber(size_t serverIndex);
		std::vector < std::string >												getLocationSpecificData(size_t serverIndex, size_t locationIndex, std::string data);
		std::vector < std::pair <std::string, std::vector < std::string > > >	getLocationData(size_t serverIndex, size_t locationIndex);
		std::vector < std::pair <std::string, std::vector < std::string > > >	serverData(size_t index);
		std::vector <  std::pair < std::string, std::string > >					getServerErrorPages(size_t index);
};
