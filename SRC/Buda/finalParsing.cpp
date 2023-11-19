/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finalParsing.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamghar <eamghar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/13 15:53:49 by ytaqsi            #+#    #+#             */
/*   Updated: 2023/11/19 21:22:53 by eamghar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Request.hpp"
#include "../../includes/webserv.hpp"

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

std::vector<std::string> Webserv::getHttpStatusCodes()
{
	return httpStatusCodes;
}


bool checkListen(std::string &data)
{
	size_t i = data.find(':');
	if (i == std::string::npos)
	{
		if (isValidPort(data))
			return true;
		return false;
	}
	if (!isValidIPAddress(data.substr(0, i)) || !isValidPort(data.substr(i + 1)))
		return false;
	return true;
}

bool checkServerData(std::vector<std::string> &data)
{
	if (data[0] == "listen" && (data.size() != 2 || !checkListen(data[1])))
	{
		std::cout << "Error on " << "\033[0;31m"  << data[0] << "\033[0m"  << std::endl;
		return false;
	}
	if (data[0] == "autoindex" && (data.size() != 2 || !isValideAutoIndex(data[1])))
	{
		std::cout << "Error on " << "\033[0;31m"  << data[0] << "\033[0m"  << std::endl;
		return false;
	}	
	if (data[0] == "upload_dir" && (data.size() != 2 || !isValideUploadDir(data[1])))
	{
		std::cout << "Error on " << "\033[0;31m"  << data[0] << "\033[0m"  << std::endl;
		return false;
	}	
	if (data[0] == "root" && (data.size() != 2 || !isValideRoot(data[1])))
	{
		std::cout << "Error on " << "\033[0;31m"  << data[0] << "\033[0m"  << std::endl;
		return false;
	}	
	if (data[0] == "client_body_max_size" && (data.size() != 2 || !isValideClientBodyMaxSize(data[1])))
	{
		std::cout << "Error on " << "\033[0;31m"  << data[0] << "\033[0m"  << std::endl;
		return false;
	}	
	if (data[0] == "error_page" && (data.size() != 3 || !isValideErrorPage(data[1])))
	{
		std::cout << "Error on " << "\033[0;31m"  << data[0] << "\033[0m"  << std::endl;
		return false;
	}
	if (data[0] == "cgi" && (data.size() != 3 || !isValideLocationCGI(data[1], data[2])))
	{
		std::cout << "Error on " << "\033[0;31m"  << data[0] << "\033[0m"  << std::endl;
		return false;
	}
	return true;
}

bool Webserv::finalConfigFileParsing()
{
	for (size_t i = 0; i < servers.size(); i++)
	{
		for (size_t j = 0; j < servers[i].size(); j++)
		{	
			std::vector<std::string> line = ft_split(servers[i][j]);
			if (line[0] == "location" && line.size() != 2)
				return false;
			if(!checkServerData(line))
				return line.clear(), false;
			line.clear();	
		}
	}
	int	listenCp;
	int	autoIndexCp;
	int	rootCp;
	int	maxSizeCp;
	int	uploadDirCp;
	
	int	locationRoot;
	int	locationMethods;
	int	locationMaxSize;
	int	locationIndex;
	int	locationuploadDir;
	for (size_t i = 0; i < servers.size(); i++)
	{
		listenCp = 0;
		autoIndexCp = 0;
		rootCp = 0;
		maxSizeCp = 0;
		uploadDirCp = 0;
		for (size_t j = 0; j < servers[i].size(); j++)
		{
			std::vector<std::string> line = ft_split(servers[i][j]);
			if (line[0] == "listen")
				listenCp++;
			if (line[0] == "autoindex")
				autoIndexCp++;
			if (line[0] == "root")
				rootCp++;
			if (line[0] == "client_body_max_size")
				maxSizeCp++;
			if (line[0] == "upload_dir")
				uploadDirCp++;
			if (line[0] == "location")
			{
				line.clear();
				locationRoot = 0;
				locationMethods = 0;
				locationMaxSize = 0;
				locationIndex = 0;
				locationuploadDir = 0;
				j++;
				while (j < servers[i].size())
				{
					line = ft_split(servers[i][j]);
					if (line[0] == "root")
						locationRoot++;
					if (line[0] == "index")
						locationIndex++;
					if (line[0] == "methods")
						locationMethods++;
					if (line[0] == "client_body_max_size")
						locationMaxSize++;
					if (line[0] == "upload_dir")
						locationuploadDir++;
					if (line[0] == "location")
					{
						--j;
						break;
					}
					line.clear();
					j++;
				}
				if (locationRoot != 1 || locationIndex > 1 || locationMethods != 1 || locationMaxSize != 1 || locationuploadDir > 1 )
				{
					std::cout << "Error in " << "\033[0;31m"  << "the location config" << "\033[0m"  << std::endl;
					return false;
				}
			}
			line.clear();
		}
		if (listenCp < 1 || autoIndexCp != 1 || rootCp != 1 || maxSizeCp != 1 || uploadDirCp > 1)
		{
			std::cout << "Error in " << "\033[0;31m"  << "the server config" << "\033[0m"  << std::endl;
			return false;
		}
	}
	return true;
}
