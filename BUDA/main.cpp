/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ytaqsi <ytaqsi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 12:12:54 by ytaqsi            #+#    #+#             */
/*   Updated: 2023/11/10 13:13:47 by ytaqsi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/webserv.hpp"

int main(int ac, char **av)
{
	Webserv webServ;
	webServ.parsing(ac, av);
	webServ.fillServerList();

	
}

