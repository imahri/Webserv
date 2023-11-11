/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   webserv.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaqsi <ytaqsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/11 15:25:18 by ytaqsi            #+#    #+#             */
/*   Updated: 2023/11/11 15:36:59 by ytaqsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/Request.hpp"

Webserv::Webserv(const Webserv& copy) : servers(copy.servers) {}

Webserv& Webserv::operator=(const Webserv& copy)
{
    if (this != &copy)
        this->servers = copy.servers;
    return *this;
}
