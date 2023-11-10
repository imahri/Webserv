/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamghar <eamghar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 02:32:10 by eamghar           #+#    #+#             */
/*   Updated: 2023/11/10 11:57:27 by eamghar          ###   ########.fr       */
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


class Request
{
    private:
        std::map<std::string, std::string> HeaderData;
        
    public:
        Request();
        Request(const Request &obj);
        Request &operator=(const Request &other);
        ~Request();
        
        int                             checkFirstLine(std::string check);
        std::string                     getNextToken(std::istringstream &iss);
        int                             checkDigit(std::string str);
        int                             checkWhiteSpace(std::string str);
        int                             checkNumbers(std::string str);
        int                             parseRequest(std::string buffer);
        int                             createServer();
        std::vector<std::string>        ft_split(std::string &s, std::string delimiter);
        std::vector<std::string>        ft_split(std::string& s, char c);
        std::vector<std::string>        ft_split(std::string& s);
        std::string&                    ft_trim(std::string& s, char c);
        std::string&                    ft_trim(std::string& s, std::string delimiter);



};

#endif