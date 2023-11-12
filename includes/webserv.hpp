/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamghar <eamghar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:46:12 by ytaqsi            #+#    #+#             */
/*   Updated: 2023/11/12 21:15:54 by eamghar          ###   ########.fr       */
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
#include <dirent.h>

#include "Request.hpp"

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


		size_t																	getServersNumber();
		size_t																	getLocationsNumber(size_t serverIndex);
		std::vector < std::string >												getLocationSingle(size_t serverIndex, size_t locationIndex, std::string data);
		std::vector < std::pair <std::string,std::string > >					getLocationMultiple(size_t serverIndex, size_t locationIndex, std::string data);
		std::vector < std::pair <std::string, std::vector < std::string > > >	getLocationData(size_t serverIndex, size_t locationIndex);
		std::vector < std::pair <std::string, std::vector < std::string > > >	serverData(size_t index);
		std::vector <  std::pair < std::string, std::string > >					getServerErrorPages(size_t index);
		bool																	isValidPort(const std::string& port);
		bool																	isValidIPAddress(const std::string& ipAddress);
		bool																	isDirectory( const std::string& path);
		bool																	isFile( const std::string& path);
		bool																	isValideAutoIndex(const std::string& autoindex);
		bool																	isValideUploadDir(const std::string& uploadDir);
		bool																	isValideRoot(const std::string& root);
		bool																	isValideClientBodyMaxSize(const std::string& clientBodyMaxSize);
};
