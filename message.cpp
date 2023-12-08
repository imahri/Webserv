#include <_types/_intmax_t.h>
#include <string>
#include <sys/_types/_size_t.h>
#include <sys/fcntl.h>
#include <sys/poll.h>
#include <sys/socket.h>
#include <vector>
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
#include <sys/time.h>
#include <signal.h>



std::vector<struct pollfd> net;

class   Server
{
    public:
        std::string ip;
        int port;
        int fd;
        int index;
        sockaddr_in serverAddr;
        // std::vector<int> vec_client; 
        std::vector<int> client;
        static size_t count;
    /*---------------------------------------------------------*/ 
        Server(){};
        Server(std::string ip, int port):ip (ip), port(port){
            index = count;
            count++;
        };
        ~Server(){};
    /*---------------------------------------------------------*/ 
};

size_t Server::count = 0;

void    theStart(Server &se)
{
    se.fd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&se.serverAddr, sizeof(se.serverAddr));
    se.serverAddr.sin_family = AF_INET;
    se.serverAddr.sin_port = htons(se.port);
    se.serverAddr.sin_addr.s_addr = INADDR_ANY;
    se.serverAddr.sin_zero[7] = '\0';
    int opt = 1;
    setsockopt(se.fd, SOL_SOCKET, SO_REUSEADDR, (void *)&opt, sizeof(opt));
    int n;
    n = bind(se.fd, (struct sockaddr *)&se.serverAddr, sizeof(se.serverAddr));
    if (n < 0)
        perror("bind");
    fcntl(se.fd, F_SETFL, O_NONBLOCK, FD_CLOEXEC);
    listen(se.fd, 1000);
}

bool found_it(int fd, std::vector<struct Server> &vec_serve)
{
    for(size_t y = 0; y < vec_serve.size(); y++)
    {
        if (vec_serve[y].fd == fd)
            return true;
    }
    return false;
}

bool found_it_poll(int fd, std::vector<struct pollfd> &vec_serve)
{
    for(size_t y = 0; y < vec_serve.size(); y++)
    {
        if (vec_serve[y].fd == fd)
            return true;
    }
    return false;
}


int finde_server(int fd, std::vector<struct Server> &vec_serve)
{
    size_t i ;
    std::cout << "\t-----------" << std::endl;
    std::cout << "\t     " <<  fd << std::endl;
    std::cout << "\t-----------" << std::endl;
    for(i = 0; i < vec_serve.size(); i++)
    {
        std::cout<< ">>>>>>>>\t" << "index: " << vec_serve[i].index << "\tport: " << vec_serve[i].port << "\tip: " << vec_serve[i].ip << "\tserver fd: " << vec_serve[i].fd << std::endl;
        if (vec_serve[i].fd == fd)
            return fd;
    }
    return -1;
}


std::vector<struct pollfd>::iterator get_iter(int fd, std::vector<struct pollfd> &net)
{
    std::vector<struct pollfd>::iterator it = net.begin();
    std::vector<struct pollfd>::iterator its = net.begin();
    for (;it != net.end(); it++)
    {
        if (it->fd == fd)
            its = it;
    }
    return its;
}
void sig(int sig)
{
    std::cout << "reacive: " << sig << std::endl;
    for (size_t tr = 0; tr < net.size(); tr++)
        std::cout << "index: " << tr  << "\trevent: " << net[tr].revents << "\tevent: " << net[tr].events << "\tfd: " << net[tr].fd << std::endl;
}



int main()
{
    signal(SIGCHLD, sig);
    Server se("127.0.0.1",5823);
    Server fe("127.0.0.1",8521);

    std::vector<struct Server> vec_serve;
    vec_serve.push_back(se);
    vec_serve.push_back(fe);

    struct pollfd tmp;
    for (size_t i = 0; i < vec_serve.size(); i++) {
        theStart(vec_serve[i]);
        tmp.fd = vec_serve[i].fd;
        tmp.events = POLLIN;
        net.push_back(tmp);
    }
    
    std::cout << "<------------------------------------------------------------>" << std::endl;
    for (size_t tr = 0; tr < vec_serve.size(); tr++)
        std::cout << "index: " << vec_serve[tr].index << "\tport: " << vec_serve[tr].port << "\tip: " << vec_serve[tr].ip << "\tserver fd: " << vec_serve[tr].fd << std::endl;
    std::cout << "<------------------------------------------------------------>" << std::endl;
    for (size_t tr = 0; tr < net.size(); tr++)
        std::cout << "index: " << tr  << "\trevent: " << net[tr].revents << "\tevent: " << net[tr].events << "\tfd: " << net[tr].fd << std::endl;
    std::cout << "<------------------------------------------------------------>" << std::endl;
    std::cout << "vec_serve: " << vec_serve.size() << std::endl;
    std::cout << "<------------------------------------------------------------>" << std::endl;

    char buffer[50000];
    signal(SIGPIPE, SIG_IGN);
    while(true)
    {
        struct timeval timeout;
        timeout.tv_sec = 5; // Timeout in seconds
        timeout.tv_usec = 1; // Timeout in microseconds
        int timeout_ms = timeout.tv_sec * 1000 + timeout.tv_usec / 1000;
        int ret = poll(net.data(), net.size(), timeout_ms);
        if (ret == -1)
        {
            continue;
        }
        if (ret == 0 || net.size() >= 10000)
        {
            for (size_t yt = vec_serve.size(); yt < net.size(); yt++)
                close(net[yt].fd);
            net.clear();
            for (size_t i = 0; i < vec_serve.size(); i++) 
            {
                tmp.fd = vec_serve[i].fd;
                tmp.events = POLLIN;
                net.push_back(tmp);
            }
        }
        for (size_t i = 0; i < net.size(); i++)
        {
            if (net[i].revents & POLLIN) 
            {
                if (found_it(net[i].fd, vec_serve) && net[i].revents & POLLIN)
                {
                    struct pollfd tmps;
                    int clientSocket = accept(net[i].fd, NULL, 0);
                    if (clientSocket == -1)
                        break;
                    tmps.fd = clientSocket;
                    tmps.events = POLLIN;
                    fcntl(clientSocket, F_SETFL, O_NONBLOCK, FD_CLOEXEC);
                    net.push_back(tmps);
                    continue;
                }
                bzero(buffer, 50000);
                int tt = recv(net[i].fd, buffer, 50000, 0);
                if (tt == 0)
                {
                    // if (net.size() == vec_serve.size())
                    //     break;
                    close(net[i].fd);
                    // std::vector<struct pollfd>::iterator yt = get_iter(net[i].fd, net);
                    // net.erase(yt);
                    continue;
                }
                else if (tt == -1)
                    continue;
                else
                {
                    std::cout << buffer << std::endl;
                    std::cout << "client: " << net[i].fd << std::endl;
                    net[i].events = POLLOUT;
                    continue;
                }
            }
            else if (net[i].revents & POLLOUT)
            {
                const char *response = "HTTP/1.1 200 OK\r\nContent-Length: 10\r\nContent-Type: text/plain\r\n\r\n";
                send(net[i].fd,response,strlen(response), 0); 
                const char *message = "hacker man";
                send(net[i].fd,message, strlen(message), 0);
                // close(net[i].fd);
                // std::vector<struct pollfd>::iterator yt = get_iter(net[i].fd, net);
                // net.erase(yt);
                net[i].events = POLLIN;
                continue;
            }
        }
    }
}