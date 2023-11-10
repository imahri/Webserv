/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   string_utils.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaqsi <ytaqsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 10:22:13 by ytaqsi            #+#    #+#             */
/*   Updated: 2023/11/10 13:13:51 by ytaqsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/webserv.hpp"

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
	int	j = 0;

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
	
	std::vector < std::vector < std::string > > serverss;
	
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
            serverss.push_back(data);
        }
    }
	
	 for (size_t i = 0; i < serverss.size(); ++i) 
	 {
        for (size_t j = 0; j < serverss[i].size(); ++j) 
		{
            std::cout << serverss[i][j] << '\n';
        }
		std::cout << "=======================" <<std::endl;
    }
	
	
	
}