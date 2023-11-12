/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eamghar <eamghar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:25:18 by ytaqsi            #+#    #+#             */
/*   Updated: 2023/11/12 17:20:22 by eamghar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/Request.hpp"

Webserv::Webserv(const Webserv& copy) : servers(copy.servers) {}

Webserv& Webserv::operator=(const Webserv& copy)
{
    if (this != &copy)
        this->servers = copy.servers;
    return *this;
}
