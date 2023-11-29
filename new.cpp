#include <cmath>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <strings.h>
#include <sys/_types/_size_t.h>
#include <sys/poll.h>
#include <sys/signal.h>
#include <sys/unistd.h>
#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <poll.h>
#include <vector>
#include <fcntl.h>
#include <iterator>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <sys/stat.h> 
#include <dirent.h>
#include <algorithm>
#include <map>
#include <vector>

int WaitForFullRequest(std::string buff)
{
    std::string substringToFind = "\r\n\r\n";

    size_t found = buff.find(substringToFind);

    if (found != std::string::npos)
    {
        size_t index = buff.find('\n');
        if (index == std::string::npos)
            return (0);

        std::string http = buff.substr(0, index - 1);
        std::vector<std::string> vec = ft_split(http, " \n\r\t");

        if (*vec.begin() == "GET" || *vec.begin() == "DELETE")
            return 1;
        else if (*vec.begin() == "POST")
        {
            size_t second = buff.find("Content-Length:") + 15;
            if (second != std::string::npos)
            {
                std::string Val = buff.substr(second, found - second);
                std::cout << "VAL: " << Val << std::endl;
                static int i;
                while (i < std::atoi(Val.c_str()))
                    i++;
                if (i == std::atoi(Val.c_str()))
                    return (i = 0, 1);
                else
                    return 0;
            }
            else
                return 0;
        }
        else
            return 0;
    }
    else
        return 0;
}