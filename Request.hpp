/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Request.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamghar <eamghar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 02:32:10 by eamghar           #+#    #+#             */
/*   Updated: 2023/11/09 21:43:26 by eamghar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef REQUEST_HPP
#define REQUEST_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <sstream>
#include <map>
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstring>
#include <unistd.h>


class Request
{
    private:
        std::map<std::string, std::string> HeaderData;
        
    public:
        Request();
        Request(const Request &obj);
        Request &operator=(const Request &other);
        ~Request();
        
        int             checkFirstLine(std::string check);
        std::string     getNextToken(std::istringstream &iss);
        int             checkDigit(std::string str);
        int             checkWhiteSpace(std::string str);
        int             checkNumbers(std::string str);
        int             parseRequest(std::string buffer);
        int             createServer();


};

#endif