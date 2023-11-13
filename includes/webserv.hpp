/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaqsi <ytaqsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 11:46:12 by ytaqsi            #+#    #+#             */
/*   Updated: 2023/11/13 16:49:00 by ytaqsi           ###   ########.fr       */
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
		std::vector<std::string> httpStatusCodes;
		std::ifstream configFile;
		std::string fileName;

	public:

		Webserv();
		Webserv(const Webserv& copy);
		Webserv&	operator = (const Webserv& copy);
		bool		parsing(int ac, char **av);
		void		fillServerList();

		bool		finalParsing();
		size_t																	getServersNumber			();
		size_t																	getLocationsNumber			(size_t serverIndex);
		
		std::vector < std::pair <std::string, std::vector < std::string > > >	serverData					(size_t index);
		std::string																getServerDataSingle			(size_t serverIndex, std::string data);
		std::vector < std::pair < std::string, std::string > >					getServerErrorPages			(size_t index);
		
		std::vector < std::pair <std::string, std::vector < std::string > > >	getLocationData				(size_t serverIndex, size_t locationIndex);
		std::vector < std::string >												getLocationSingle			(size_t serverIndex, size_t locationIndex, std::string data);
		std::vector < std::pair <std::string,std::string > >					getLocationMultiple			(size_t serverIndex, size_t locationIndex, std::string data);
		
		bool																	isValidPort					(const std::string& port);
		bool																	isValidIPAddress			(const std::string& ipAddress);
		bool																	isDirectory					( const std::string& path);
		bool																	isFile						( const std::string& path);
		bool																	isValideAutoIndex			(const std::string& autoindex);
		bool																	isValideUploadDir			(const std::string& uploadDir);
		bool																	isValideRoot				(const std::string& root);
		bool																	isValideClientBodyMaxSize	(const std::string& clientBodyMaxSize);
		bool																	isValideErrorPage			(const std::string &err, const std::string &errPage);
		bool																	isValideLocationPath		(const std::string &uri);

		bool																	isValideLocationMethods		(const std::string &method);
		bool																	isValideLocationCGI			(const std::string &cgi, const std::string &cgiFile);
		bool																	isValideLocationRedirect	(const std::string &nbr, const std::string &page);
};
