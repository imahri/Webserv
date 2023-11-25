#pragma once

#include "Webserv.hpp"

class Client
{
    public:
        int fd;
        bool isEnd;
        char *buffer[1024];
        Client(int fd):fd(fd),isEnd(false){};
        ~Client();
};

class Server
{
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

class IoMultiplexing
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
        int     StartTheMatrix(Parsing &ps);
        IoMultiplexing(){};
        ~IoMultiplexing(){};
};


