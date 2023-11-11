/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamghar <eamghar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:46:12 by ytaqsi            #+#    #+#             */
/*   Updated: 2023/11/11 18:51:29 by eamghar          ###   ########.fr       */
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

bool ft_isAllSpace(std::string &s);

struct Location
{
    std::string path;
    std::string root;
    std::vector<std::string> methods;
    std::string uploadDir;
    std::string cgiPhp;
    std::string cgiPy;
    std::string redirect;
};

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
		std::vector < std::pair <std::string,std::string > >					getLocationSpecificDatas(size_t serverIndex, size_t locationIndex, std::string data);
		std::vector < std::pair <std::string, std::vector < std::string > > >	getLocationData(size_t serverIndex, size_t locationIndex);
		std::vector < std::pair <std::string, std::vector < std::string > > >	serverData(size_t index);
		std::vector <  std::pair < std::string, std::string > >					getServerErrorPages(size_t index);
};
