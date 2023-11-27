


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


class Client
{
    public:
        int fd;
        bool isEnd;
        char *buffer[1024];
        Client(int fd):fd(fd),isEnd(false){};
        ~Client();
};

class Server{
    public:
        int port;
        std::string ip;
        int serversocket;
        struct sockaddr a;
        std::vector<Client *> sudo_client;
        sockaddr_in serverAddr;
        Server(){};
        Server(int port, std::string    ip);//set
        ~Server(){};
        static int nbr_srv;
        void    start();
};

int Server::nbr_srv = 0;

Server::Server(int port, std::string    ip)
{
    this->ip = ip;
    this->port = port;
};

// void    Server::start()
// {
//     this->serversocket = socket(AF_INET, SOCK_STREAM, 0);
//     bzero(&this->serverAddr, sizeof(this->serverAddr));
//     this->serverAddr.sin_family = AF_INET;
//     this->serverAddr.sin_port = htons(this->port);
//     this->serverAddr.sin_addr.s_addr = INADDR_ANY;
//     this->serverAddr.sin_zero[7] = '\0';
//     int opt = 1;
//     setsockopt(this->serversocket,SOL_SOCKET, SO_REUSEADDR,&opt, (opt));
//     int n;
//     n = bind(this->serversocket, (struct sockaddr *)&this->serverAddr, sizeof(this->serverAddr));
//     if (n < 0)
//         perror("wa bzaaaaf");
//     fcntl(this->serversocket, F_SETFL, O_NONBLOCK, FD_CLOEXEC);
//     listen(serversocket, 1000);
//     nbr_srv++;
// }
void Server::start()
{
    this->serversocket = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&this->serverAddr, sizeof(this->serverAddr));
    this->serverAddr.sin_family = AF_INET;
    this->serverAddr.sin_port = htons(this->port);
    this->serverAddr.sin_addr.s_addr = INADDR_ANY;
    this->serverAddr.sin_zero[7] = '\0';
    int opt = 1;
    setsockopt(this->serversocket, SOL_SOCKET, SO_REUSEADDR, (void*)&opt, sizeof(opt));
    int n;
    n = bind(this->serversocket, (struct sockaddr*)&this->serverAddr, sizeof(this->serverAddr));
    if (n < 0)
        perror("wa bzaaaaf");
    fcntl(this->serversocket, F_SETFL, O_NONBLOCK);
    listen(this->serversocket, 1000);
    nbr_srv++;
}

class Webserve
{
    public:
        std::vector<Server> sudo_apt;
       
        static std::vector<struct pollfd> net;
        static int maxfd;
        bool    isServer(int fd);
        void    acceptNewClient(int fd);
        int     foundServer(int fd);
        std::vector<Client *>::iterator         checkClient(int fd);
        std::vector<Server>::iterator           checkServer(int fd);
        bool    isDoneRequest(char *str);
        Webserve(){};
        ~Webserve(){};
};

int Webserve::maxfd = 0;
std::vector<struct pollfd> Webserve::net;


bool    Webserve::isDoneRequest(char *str)
{
    if (strcmp("/r/n/r/n", str))
        return true;
    return false;
}

bool isElementInVector(std::vector<int>& vec, int element)
{
    std::vector<int>::iterator itr;
    itr = std::find(vec.begin(), vec.end(), element);

    return itr != vec.end();
}

bool    Webserve::isServer(int fd)
{
    std::vector<Server>::iterator itr = sudo_apt.begin();

    for (; itr != sudo_apt.end(); itr++)
    {
        if (fd == itr->serversocket)
            return true;
    }
    return false;
}

int     Webserve::foundServer(int fd)
{
    int i = 0;
    std::vector<Server>::iterator itr = sudo_apt.begin();
    for(; itr != sudo_apt.end(); itr++)
    {
        if (fd == itr->serversocket)
            return i;
        i++;
    }
    return -1;
}

void    Webserve::acceptNewClient(int fd)
{
    int clientSocket = accept(fd, NULL, 0);
    struct pollfd tmp;
    tmp.fd = clientSocket;
    tmp.events = POLLIN | POLLOUT;
    fcntl(clientSocket, F_SETFL, O_NONBLOCK, FD_CLOEXEC);
    Webserve::net.push_back(tmp);
    int finder = foundServer(fd);
    if (finder != -1)
    {
        Client *cr = new Client(clientSocket);
        sudo_apt[finder].sudo_client.push_back(cr);
    }
}

std::vector<Client *>::iterator    Webserve::checkClient(int fd)
{
    std::vector<Client *>::iterator fin;
    std::vector<Server>::iterator itr = sudo_apt.begin();
    for(; itr != sudo_apt.end(); itr++)
    {
        std::vector<Client *>::iterator itrs = itr->sudo_client.begin();
        for(; itrs != itr->sudo_client.end(); itrs++)
        {
            if (fd == (*itrs)->fd)
                fin =  itrs;
        }
    }
    return fin;
}

std::vector<Server>::iterator    Webserve::checkServer(int fd)
{
    std::vector<Server>::iterator fin;
    std::vector<Server>::iterator itr = sudo_apt.begin();
    for(; itr != sudo_apt.end(); itr++)
    {
        std::vector<Client *>::iterator itrs = itr->sudo_client.begin();
        for(; itrs != itr->sudo_client.end(); itrs++)
        {
            if (fd == (*itrs)->fd)
                fin =  itr;
        }
    }
    return fin;
}

int main()
{
    Webserve re;
    Server qw(3005,"0.0.0.0");
    Server qwe(3006,"0.0.0.0");
    char buffer[3001];
    std::vector<Server> tr;
    tr.push_back(qw);
    tr.push_back(qwe);
    re.sudo_apt.push_back(qw);
    re.sudo_apt.push_back(qwe);
    size_t  ll = re.sudo_apt.size();

    for (size_t i = 0; i < ll; i++)
    {
        re.sudo_apt[i].start();
        struct pollfd tmp;
        tmp.fd = re.sudo_apt[i].serversocket;
        tmp.events = POLLIN;
        Webserve::net.push_back(tmp);
    }
    signal(SIGPIPE, SIG_IGN);
    while(true)
    {
        int ret = poll(Webserve::net.data(), Webserve::net.size(), 0);
        for (size_t j = 0; j < Webserve::net.size() && ret; j++)
        {
                if (re.isServer(Webserve::net[j].fd) && Webserve::net[j].revents & POLLIN)
                {
                    re.acceptNewClient(Webserve::net[j].fd);
                    continue;
                }
                else if (j >= Server::nbr_srv){
                
                    if (Webserve::net[j].revents & POLLIN)
                    {
                        while(1)
                        {
                            bzero(buffer, 3000);
                            int tt = recv(Webserve::net[j].fd, buffer,3000, 0);
                            std::cout << "===>> " << tt << std::endl;
                            if (tt == 0)
                            {
                                close(Webserve::net[j].fd);
                            }
                            else if (tt < 0)
                                break;
                            std::cout << buffer << std::endl;
                        }
                        if (re.isDoneRequest(buffer))
                        {
                            Webserve::net[j].events = POLLOUT;
                            Webserve::net[j].revents = 0;
                        }
                        continue;
                    }
                    else if (Webserve::net[j].revents & POLLOUT){
                        const char *response = "HTTP/1.1 200 OK\r\nContent-Length: 10\r\nContent-Type: text/plain\r\n\r\n"; // here start the response send 500000
                        const char *message = "hacker men";
                        send(Webserve::net[j].fd, response, strlen(response), 0);
                        send(Webserve::net[j].fd, message, strlen(message), 0);
                        Webserve::net[j].events = POLLIN;

                    }
                    // if (Webserve::net[j].revents & POLLERR | POLLHUP)
                    // {
                    //     //close clien and erase it 
                    // }
                }
                
            // ret--;
        }
    }
}