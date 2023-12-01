#pragma once

#include "Webserv.hpp"

class Client
{
    public:
        int fd;
        bool isEnd;
        bool keepAlive;
        char *buffer[1024];
        Client(int fd):fd(fd),isEnd(false),keepAlive(false){};
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
        int index;
        void    start();
};

class IoMultiplexing
{
    public:
        std::vector<Server> sudo_apt;
        std::map<int, std::pair<std::string, std::string> > request_msg;
        static std::vector<struct pollfd> net;
        static int maxfd;
        bool    isServer(int fd);
        void    acceptNewClient(int fd);
        int     foundServer(int fd);
        std::vector<Client *>::iterator         checkClient(int fd);
        int           checkServer(int fd);
        bool    isDoneRequest(char *str);
        int     StartTheMatrix(Parsing &ps);
        IoMultiplexing(){};
        ~IoMultiplexing(){};
};


