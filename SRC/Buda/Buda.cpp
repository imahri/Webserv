/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Buda.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaqsi <ytaqsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/12 15:20:14 by ytaqsi            #+#    #+#             */
/*   Updated: 2023/11/15 16:41:42 by ytaqsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Request.hpp"
#include "../../includes/webserv.hpp"

bool isValidPort(const std::string& port)
{
	std::istringstream ss(port);
	int portNumber;
	ss >> portNumber;
	return (!ss.fail() && ss.eof() && portNumber >= 0 && portNumber <= 65535);
}

bool isValidIPAddress(const std::string& ipAddress)
{
	std::istringstream ss(ipAddress);
	std::string octet;
	std::vector<int> octets;

	while (std::getline(ss, octet, '.'))
	{
		int num = std::atoi(octet.c_str());
		if (num < 0 || num > 255) 
			return false; 
		if (octet.length() > 1 && octet[0] == '0') 
			return false;
		octets.push_back(num);
	}
	return (octets.size() == 4);
}

bool isDirectory( const std::string& path)
{
	
	struct stat fileInfo;
	if (stat(path.c_str(), &fileInfo) != 0)
		return false;
	return S_ISDIR(fileInfo.st_mode);
}

bool isFile( const std::string& path)
{
	struct stat fileInfo;
	if (stat(path.c_str(), &fileInfo) != 0)
		return false;
	return S_ISREG(fileInfo.st_mode);
}

bool isValideAutoIndex(const std::string& autoindex)
{
	if (autoindex != "on" && autoindex != "off")
		return false;
	return true;
}

bool isValideUploadDir(const std::string& uploadDir)
{
	return isDirectory(uploadDir);
}
bool isValideRoot(const std::string& root)
{
	return isDirectory(root);
}

bool isValideClientBodyMaxSize(const std::string& clientBodyMaxSize)
{
	int cp = 0;

	std::string::const_reverse_iterator it = clientBodyMaxSize.rbegin();
	for (; it != clientBodyMaxSize.rend(); ++it)
	{
		if (*it == 'G' || *it == 'M' || *it == 'K' || *it == 'B')
		{
			cp++;
			continue;
		}
		else
			break;
	}
	if (cp != 1)
		return false;
	for (; it != clientBodyMaxSize.rend(); ++it)
	{
		if (!std::isdigit(*it))
			return false;
	}
	return true;
}


bool isValideLocationPath(const std::string &uri)
{
	std::string::const_iterator it = uri.begin();

	int	cp = 0;
	
	while(it != uri.end() && *it == '/')
	{
		cp++;
		it++;
	}
	
	if (cp != 1)
		return false;
	
	// if (!isDirectory(uri))
	// 	return false;
	
	return true;
}

bool isValideLocationMethods(const std::string &method)
{
	if (method != "POST" && method != "DELETE" && method != "GET")
		return false;
	return true;
}


bool isValideLocationCGI (const std::string &cgi, const std::string &cgiFile)
{
	if (cgi != "py" && cgi != "php")
		return false;

	if (!isFile(cgiFile))
		return false;
	return true;
}

// bool isValideLocationRedirect(const std::string &nbr, const std::string &page)
// {

// 	std::vector<std::string>::iterator it = std::find(httpStatusCodes.begin(), httpStatusCodes.end(), nbr);
	
// 	if (it == httpStatusCodes.end() || !isFile(page))
// 		return false;
	
// 	return true;
// }


bool isValideErrorPage			(const std::string &err, const std::string &errPage)
{
	Webserv w;
	std::vector<std::string> codes = w.getHttpStatusCodes();
	std::vector<std::string>::iterator it = std::find(codes.begin(), codes.end(), err);
	
	if (it == codes.end() || !isFile(errPage))
		return false;
	
	return true;
}
