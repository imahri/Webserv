/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pars.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imahri <imahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 18:03:10 by imahri            #+#    #+#             */
/*   Updated: 2023/11/08 10:40:01 by imahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cctype>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>



bool get_line(std::ifstream& inputFile)
{
    bool val = 0;
    size_t ob = 0;
    size_t cb = 0;

    std::string data;
    std::getline(inputFile,data);
    if(data != "server")
    {
        std::cout << "9lawi" << std::endl;
        return false;
    }
    while (std::getline(inputFile,data))
    {
        ob += std::count(data.begin(),data.end(),'{');
        cb += std::count(data.begin(),data.end(),'}');
    }
    if ((ob - cb) != 0)
    {
        std::cout << "9lawi" << std::endl;
        return false;
    }
    std::cout << "nadi" << std::endl;
    return true;
}

int main(int ac, char **av)
{
    (void)ac;
    std::ifstream inputFile;

    inputFile.open(av[1]);

    get_line(inputFile);

    inputFile.close();
}

