#pragma once

#include "Webserv.hpp"

class Client
{
    public:
        std::string c_request;
        std::string c_response;
        std::string path;
        std::streampos initialPosition;
        std::streamsize bytesRead;
        std::streampos currentPosition;
        int         fd;

        bool send_file;
        bool keepAlive;
        bool header;
        char buffer[1024];
        Client():send_file(false),keepAlive(false),header(false)
        {
            c_request.clear();
            c_response.clear();
            path.clear();
        };
};

class Server
{
    public:
        struct addrinfo hints, *res;
        int port;
        std::string ip;
        int serversocket;
        int fd;
        std::string serverName;
        struct sockaddr a;
        std::vector<Client *> sudo_client;
        Server(){};
        Server(int port, std::string    ip);//set
        ~Server();
        static int nbr_srv;
        int index;
        void    start();
};

class IoMultiplexing
{
    public:
        std::vector<Server> sudo_apt;
        std::map<int, Client> request_msg;
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
    void    clearClinet(int fd, std::map<int, Client> &request_msg);

};


