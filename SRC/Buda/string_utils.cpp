/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaqsi <ytaqsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:22:13 by ytaqsi            #+#    #+#             */
/*   Updated: 2023/11/13 16:50:24 by ytaqsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Request.hpp"

std::vector<std::string> ft_split(std::string& s, std::string delimiter)
{
	std::vector<std::string> arr;
	std::string current;
	size_t size = s.size();

	for (size_t i = 0; i < size; i++) 
	{
		while (delimiter.find(s[i]) != std::string::npos)
			i++;
		while (i < size && delimiter.find(s[i]) == std::string::npos)
			current += s[i++];
		if (!current.empty()) 
		{
			arr.push_back(current);
			current.clear();
		}
	}
	return arr;
}

std::vector<std::string> ft_split(std::string& s, char c)
{
	std::vector<std::string> arr;
	std::string			line;
	std::istringstream	iss(s);
	
	while (std::getline(iss, line, c))
		arr.push_back(line);
	return arr;
}

std::vector<std::string> ft_split(std::string& s)
{
	std::vector<std::string> arr;
	std::string			line;
	std::istringstream	iss(s);
	
	while (iss >> line)
		arr.push_back(line);
	return arr;
}

std::string& ft_trim(std::string& s, char c)
{
	size_t i = 0;
	while (i < s.size() && s[i] == c) 
		s.erase(i, 1);

	i = s.size() - 1;
	if (i == std::string::npos)
		return s;
	while (i >= 0 && s[i] == c) 
	{
		s.erase(i, 1);
		i--; 
	}

	return s;
}

std::string ft_trim(std::string s, std::string delimiter)
{
	size_t i = 0;

    
    while (i < s.size() && delimiter.find(s[i]) != std::string::npos)
        s.erase(i, 1);

    i = s.size();
    while (i > 0 && delimiter.find(s[i - 1]) != std::string::npos)
    {
        i--;
        s.erase(i, 1);
    }

	return s;
}

bool	ft_isAllSpace(std::string& s)
{
	for (size_t i = 0; i < s.size(); i++)
	{
		if (!std::isspace(s[i]))
			return false;
	}
	return true;
}

bool	Webserv::parsing(int ac, char **av)
{
	if (ac > 2)
	{
		std::cerr << "Arrgs Error" << std::endl;
		return false;
	}
	this->fileName = "default.conf";
	if (av[1])
		fileName = av[1];
	this->configFile.open(fileName);
	if (!this->configFile)
	{
		std::cerr << "Unable to open the file " << fileName << std::endl;
		return false;
	}

	std::string					line;
	std::vector <std::string>	pars;
	std::vector <parsingStruct>	parsLast;
	size_t	j = 0;

	while (std::getline(configFile, line))
	{
		if (line.empty() || ft_isAllSpace(line) || (!line.empty() && ft_trim(line, ' ')[0] == '#'))
			continue;
		pars = ft_split(line);
		if (!pars[0].empty() && pars[0] == "server")
		{
			if (pars.size() != 2 || pars[0] != "server" || pars[1] != "{")
			{
				std::cerr << "Error in the server config" << std::endl;
				return false;
			}
			parsingStruct parsingData = {"server", true, false};
			parsLast.push_back(parsingData);
		}
		else if (!pars[0].empty() && pars[0] == "location")
		{
			if (pars.back() != "{")
			{
				std::cerr << "Error in the server location config" << fileName << std::endl;
				return false;
			}
			parsingStruct parsingData = {"location", true, false};
			parsLast.push_back(parsingData);
		}
		else if (pars.size() == 1 && !pars.front().empty() && pars.front() == "}" && j < parsLast.size())
			parsLast[j++].close_bracket = true;
		else if (!pars.back().empty() && !pars[0].empty() 
			&& pars[0] != "server" && pars[0] != "location" &&  pars.back().back() != ';')
		{
			std::cerr << "Error ; missing" << std::endl;
			return false;
		}
	}
	for (size_t i = 0; i < parsLast.size(); i++)
	{
		if (parsLast[i].open_bracket == false || parsLast[i].close_bracket == false)
		{
			{
				std::cerr << "Error { or } missing" << fileName << std::endl;
				return false;
			}
		}
	}
	configFile.close();
	return true;
}

void	Webserv::fillServerList()
{
	std::string					line;
	std::string					finalLine;

	this->configFile.open(fileName);
	if (!this->configFile)
	{
		std::cerr << "Unable to open the file |" << fileName << std::endl;
		return ;
	}

	while (std::getline(configFile, line))
	{
		std::string	trimedLine = ft_trim(line, " \t");
		if ((trimedLine[0] != '#' && trimedLine.find('#') != std::string::npos))
		{
			std::cout << "Error corrupted file" << std::endl;
			return; 
		}
		if (line.empty() || ft_isAllSpace(line) || (!line.empty() && trimedLine[0] == '#'))
			continue;
		
		finalLine += trimedLine;
	}

	std::vector <std::string>	pars(ft_split(finalLine, "\n{};"));
	std::vector <std::string>	finalParams;
	std::vector <std::string>	params;

	for (size_t i = 0;i < pars.size(); i++)
		finalParams.push_back(ft_trim(pars[i], " \t"));

	for (size_t i = 0; i < finalParams.size(); ++i) 
	{
		if (finalParams[i] == "server") 
		{
		std::vector<std::string> data;

		for (++i; i < finalParams.size(); ++i) 
		{
			if (finalParams[i] == "server") 
			{
				--i; 
				break;
			}
				data.push_back(finalParams[i]);
			}
			this->servers.push_back(data);
		}
	}
}

size_t	Webserv::getServersNumber()
{
	return (int)this->servers.size();
}


size_t		Webserv::getLocationsNumber(size_t index)
{
	int	cp = 0;

	if (index < 1 || index > servers.size())
		return -1;
	for (size_t i = 0; i < this->servers.size(); i++)
	{
		if (i == index - 1)
		{
			for (size_t j = 0; j < servers[i].size(); j++)
			{
				if (ft_split(servers[i][j])[0] == "location")
				{
					cp++;
				}
			}
		}
	}
	return cp;
}

std::vector < std::pair <std::string, std::vector < std::string > > > Webserv::getLocationData(size_t serverIndex, size_t locationIndex)
{
	std::vector < std::pair <std::string, std::vector < std::string > > > locationData;
	
	if (getLocationsNumber(serverIndex) < 1)
		return locationData;
	size_t	cp = 0;
	for (size_t i = 0; i < this->servers.size(); i++)
	{
		if (i == serverIndex - 1)
		{
			for (size_t j = 0; j < servers[i].size(); j++)
			{
				std::vector < std::string > line = ft_split(servers[i][j]);
				if (line[0] == "location")
				{
					if (cp == locationIndex - 1)
					{
						while (j < servers[i].size())
						{
							std::vector < std::string > line = ft_split(servers[i][j]);
							std::vector < std::string > values (line.begin() + 1, line.end());
							locationData.push_back(std::make_pair(line[0], values));
							j++;
							if (ft_split(servers[i][j])[0] == "location")
								break;
						}
						
					}
					cp++;
				}
			}
		}
	}
	return locationData;

}

std::vector < std::string >	Webserv::getLocationSingle(size_t serverIndex, size_t locationIndex, std::string data)
{
	std::vector < std::pair <std::string, std::vector < std::string > > > locationData (getLocationData(serverIndex, locationIndex));

	for (size_t i = 0; i < locationData.size(); i++)
	{
		if (locationData[i].first == data)
			return locationData[i].second;
	}
	return std::vector<std::string>();
}

std::vector < std::pair <std::string, std::string > > Webserv::getLocationMultiple(size_t serverIndex, size_t locationIndex, std::string dataToSearch)
{
	std::vector < std::pair <std::string, std::vector < std::string > > > locationData = getLocationData(serverIndex, locationIndex);
	std::vector < std::pair <std::string, std::string > > data;
	
	for (size_t i = 0; i < locationData.size(); i++)
	{
		if (locationData[i].first == dataToSearch)
		{
        	data.push_back(std::make_pair(locationData[i].second[0], locationData[i].second[1]));
		}
	}
	return data;
}



std::vector < std::pair <std::string, std::vector < std::string > > >	Webserv::serverData(size_t index)
{
	std::vector < std::pair <std::string, std::vector < std::string > > > serverData;
	if (index < 1 || index > servers.size())
		return serverData;
	
	for (size_t i = 0; i < this->servers.size(); i++)
	{
		if (i == index - 1)
		{
			for (size_t j = 0; j < servers[i].size(); j++)
			{
				std::vector < std::string > line = ft_split(servers[i][j]);
				if (line[0] == "listen" || line[0] == "server_name" || line[0] == "autoindex")
				{
					std::vector < std::string > values (line.begin() + 1, line.end());
					serverData.push_back(std::make_pair(line[0], values));
				}
			}
		}
	}
	return serverData;
}

std::vector < std::pair < std::string, std::string > > Webserv::getServerErrorPages(size_t index)
{
	std::vector <  std::pair < std::string, std::string > > errorPages;
	if (index < 1 || index > servers.size())
		return errorPages;
	for (size_t i = 0; i < this->servers.size(); i++)
	{
		if (i == index - 1)
		{
			for (size_t j = 0; j < servers[i].size(); j++)
			{
				std::vector < std::string > line = ft_split(servers[i][j]);
				if (line[0] == "error_page")
					errorPages.push_back(std::make_pair(line[1], line[2]));
			}
		}
	}
	return errorPages;
}

std::string Webserv::getServerDataSingle (size_t serverIndex, std::string data)
{
	if (serverIndex < 1 || serverIndex > servers.size())
		return NULL;
	for (size_t i = 0; i < this->servers.size(); i++)
	{
		if (i == serverIndex - 1)
		{
			for (size_t j = 0; j < servers[i].size(); j++)
			{
				std::vector < std::string > line = ft_split(servers[i][j]);
				if (line[0] == data)
					return line[1];
			}
		}
	}
	return NULL;
}

