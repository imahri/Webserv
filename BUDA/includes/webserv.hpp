/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaqsi <ytaqsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:46:12 by ytaqsi            #+#    #+#             */
/*   Updated: 2023/11/10 10:44:00 by ytaqsi           ###   ########.fr       */
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

std::vector<std::string> ft_split(std::string &s, std::string delimiter);
std::vector<std::string> ft_split(std::string &s, char c);
std::vector<std::string> ft_split(std::string &s);

std::string ft_trim(std::string s, std::string delimiter);
std::string &ft_trim(std::string &s, char c);

bool ft_isAllSpace(std::string &s);

struct parsingStruct
{
	std::string name;
	bool open_bracket;
	bool close_bracket;
};

struct Location
{
	std::string name;
	std::vector < std::pair < std::string, std::vector<std::string > > > locationData;
};

struct Server
{
	std::vector < std::pair < std::string, std::vector<std::string > > > serverData;
	std::vector < Location > locations;
};

class Webserv
{
	private:
		std::vector < Server > servers;
		std::ifstream configFile;
		std::string fileName;

	public:
		bool	parsing(int ac, char **av);
		void	fillServerList();
};
