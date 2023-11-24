#include <cmath>
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
        std::string reque;
        Client(int fd){
            isEnd = false;
            this->fd = fd;
        };
        ~Client(){};
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

class Webserve
{
    public:
        std::vector<Server> sudo_apt;
       
        static std::vector<struct pollfd> net;
        static int maxfd;
        bool    isServer(int fd);
        void    acceptNewClient(int fd);
        int     foundServer(int fd);
        int     checkClient(int fd);
        int     checkServer(int fd);
        bool    isDoneRequest(char *str, int fd, int index);
        Webserve(){};
        ~Webserve(){};
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


int Webserve::maxfd = 0;
std::vector<struct pollfd> Webserve::net;


bool    Webserve::isDoneRequest(char *str, int fd, int index)
{
    // std::cout << fd << "\t" << index << std::endl;
    // std::cout << Webserve::sudo_apt[fd].sudo_client[index]->isEnd << std::endl;
    // if(Webserve::sudo_apt[index].sudo_client[fd]->isEnd == false)
    // {
        // Webserve::sudo_apt[index].sudo_client[fd]->reque += str;
        // size_t     first = Webserve::sudo_apt[index].sudo_client[fd]->reque.find_first_of("\r\n\r\n");
        // if(first != Webserve::sudo_apt[index].sudo_client[fd]->reque.npos)
        // {
        //     size_t     last = Webserve::sudo_apt[index].sudo_client[fd]->reque.find_last_of("\r\n\r\n");
        //     if(last != Webserve::sudo_apt[index].sudo_client[fd]->reque.npos && last != first)
        //     {
        //         Webserve::sudo_apt[index].sudo_client[fd]->isEnd = true;
        //         return true;
        //     }
        // }
    // }
    return(true);
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
    // bzero(void *, size_t);
    struct pollfd tmp;
    tmp.fd = clientSocket;
    tmp.events = POLLIN;
    fcntl(clientSocket, F_SETFL, O_NONBLOCK, FD_CLOEXEC);
    Webserve::net.push_back(tmp);
    int finder = foundServer(fd);
    Client *cr = new Client(clientSocket);
    sudo_apt[finder].sudo_client.push_back(cr);

}

int    Webserve::checkClient(int fd)
{
    std::vector<Server>::iterator itr = sudo_apt.begin();
    for(size_t i = 0; i < sudo_apt.size(); i++)
    {
        for(size_t j = 0; sudo_apt[i].sudo_client.size(); j++)
        {
            if (fd == sudo_apt[i].sudo_client[j]->fd)
                return j;
        }
    }
    return 0;
}

int    Webserve::checkServer(int fd)
{
    std::vector<Server>::iterator itr = sudo_apt.begin();
    for(size_t i = 0; i < sudo_apt.size(); i++)
    {
        for(size_t j = 0; sudo_apt[i].sudo_client.size(); j++)
        {
            if (fd == sudo_apt[i].sudo_client[j]->fd)
                return i;
        }
    }
    return 0;
}

int main()
{
    Webserve re;
    Server qw(3005,"10.13.4.2");
    Server qwe(3006,"10.13.4.2");
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
                            if (tt == 0)
                            {
                                close(Webserve::net[j].fd);
                            }
                            else if (tt < 0)
                                break;
                            std::cout << buffer << std::endl;
                        }
                        int inclient = re.checkClient(Webserve::net[j].fd);
                        int inserver = re.checkServer(Webserve::net[j].fd);
                        // should be called


                        std::cout <<"inserver: " << inserver << "\tinclient: " << inclient << std::endl;
                        std::cout << "stttt: " << re.sudo_apt[inserver].sudo_client[inclient]->reque << std::endl;
                        // std::cout << "msg: " << re.sudo_apt[0].sudo_client[j]->reque << std::endl;
                        // std::cout << "fd: " << re.sudo_apt[0].sudo_client[j]->fd << std::endl;
                        
                        Webserve::net[j].events = POLLOUT;
                        Webserve::net[j].revents = 0;
                        continue;
                    }
                    else if (Webserve::net[j].revents & POLLOUT){
                        // std::cout << Webserve::net[j].fd << std::endl;
                        //response
                        // if data end
                        const char response[50000] = "HTTP/1.1 200 OK\r\nContent-Length: 10\r\nContent-Type: text/plain\r\n\r\n"; // here start the response send 500000
                        const char message[50000] = "hacker men";
                        send(Webserve::net[j].fd, response, strlen(response), 0);
                        send(Webserve::net[j].fd, message, strlen(message), 0);
                        // if (re.isDoneRequest(buffer))
                        Webserve::net[j].events = POLLIN;

                    }
                //     // if (Webserve::net[j].revents & POLLERR | POLLHUP)
                //     // {
                //     //     //close clien and erase it 
                //     // }
                }
                
            // ret--;
        }
    }
}