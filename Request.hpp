/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamghar <eamghar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 02:32:10 by eamghar           #+#    #+#             */
/*   Updated: 2023/11/10 22:36:42 by eamghar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>

#include <algorithm>
#include <map>
#include <vector>


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

class Request
{
    private:
        std::map<std::string, std::string>  HeaderData;
        std::string                         header;
        std::string                         body;
    	std::string                         line;
    	std::string                         http;
    	std::string                         httpVersion;
    	std::string                         methode;
    	std::string                         URI;
        size_t                              index;
        size_t                              statusCode;
        unsigned long long                  clientMaxBodySize;
        std::vector<Location>               locations;

        
    public:
        Request();
        Request(const Request &obj);
        Request &operator=(const Request &other);
        ~Request();
        
        int                                 createServer();
        int                                 getRequest(std::string buffer);
        int                                 fillHeaderAndBody(std::string buffer);
        int                                 parseRequest();
        int                                 checkHttp();
        int                                 checkBody();
        int                                 checkHeader();
        int                                 GET();
        int                                 POST();
        int                                 DELETE();

        
        //extra functions
        unsigned long long                  convertToBytes(const std::string& sizeString);
        std::string                         getNextToken(std::istringstream &iss);
        int                                 checkDigit(std::string str);
        int                                 checkWhiteSpace(std::string str);
        int                                 checkNumbers(std::string str);
        std::vector<std::string>            ft_split(std::string &s, std::string delimiter);
        std::vector<std::string>            ft_split(std::string& s, char c);
        std::vector<std::string>            ft_split(std::string& s);
        std::string&                        ft_trim(std::string& s, char c);
        std::string&                        ft_trim(std::string& s, std::string delimiter);
        int                                 fillLocations();



};

#endif