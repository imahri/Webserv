#include "../../includes/Server.hpp"

#include <sys/time.h>

int Server::nbr_srv = 0;

Server::Server(int port, std::string ip)
{
    this->ip = ip;
    this->port = port;
};

void Server::start()
{
    nbr_srv++;
    index = 0;
    serverName = "server" + std::to_string(nbr_srv);

    this->serversocket = socket(AF_INET, SOCK_STREAM, 0);
    this->fd = this->serversocket;
    bzero(&this->serverAddr, sizeof(this->serverAddr));
    this->serverAddr.sin_family = AF_INET;
    this->serverAddr.sin_port = htons(this->port);
    this->serverAddr.sin_addr.s_addr = INADDR_ANY;
    this->serverAddr.sin_zero[7] = '\0';
    int opt = 1;
    setsockopt(this->serversocket, SOL_SOCKET, SO_REUSEADDR, (void *)&opt, sizeof(opt));
    int n;
    n = bind(this->serversocket, (struct sockaddr *)&this->serverAddr, sizeof(this->serverAddr));
    if (n < 0)
        perror("wa bzaaaaf");
    fcntl(this->serversocket, F_SETFL, O_NONBLOCK);
    listen(this->serversocket, 1000);
    index = nbr_srv;
}

int IoMultiplexing::maxfd = 0;
std::vector<struct pollfd> IoMultiplexing::net;

bool IoMultiplexing::isDoneRequest(char *str)
{
    if (strcmp("/r/n/r/n", str))
        return true;
    return false;
}

bool isElementInVector(std::vector<int> &vec, int element)
{
    std::vector<int>::iterator itr;
    itr = std::find(vec.begin(), vec.end(), element);

    return itr != vec.end();
}

bool IoMultiplexing::isServer(int fd)
{
    std::vector<Server>::iterator itr = sudo_apt.begin();

    for (; itr != sudo_apt.end(); itr++)
    {
        if (fd == itr->serversocket)
            return true;
    }
    return false;
}

int IoMultiplexing::foundServer(int fd)
{
    int i = 0;
    std::vector<Server>::iterator itr = sudo_apt.begin();
    for (; itr != sudo_apt.end(); itr++)
    {
        if (fd == itr->serversocket)
            return i;
        i++;
    }
    return -1;
}

void IoMultiplexing::acceptNewClient(int fd)
{
    int clientSocket = accept(fd, NULL, 0);
    struct pollfd tmp;
    tmp.fd = clientSocket;
    tmp.events = POLLIN;
    fcntl(clientSocket, F_SETFL, O_NONBLOCK, FD_CLOEXEC);
    IoMultiplexing::net.push_back(tmp);
    int finder = foundServer(fd);
    if (finder != -1)
    {
        Client *cr = new Client(clientSocket);
        sudo_apt[finder].sudo_client.push_back(cr);
    }
    std::cout << "New client connected to server " << sudo_apt[finder].serverName << " <<\t>>" << finder << std::endl;
}

std::vector<Client *>::iterator IoMultiplexing::checkClient(int fd)
{
    std::vector<Client *>::iterator fin;
    std::vector<Server>::iterator itr = sudo_apt.begin();
    for (; itr != sudo_apt.end(); itr++)
    {
        std::vector<Client *>::iterator itrs = itr->sudo_client.begin();
        for (; itrs != itr->sudo_client.end(); itrs++)
        {
            if (fd == (*itrs)->fd)
                fin = itrs;
        }
    }
    return fin;
}

int IoMultiplexing::checkServer(int fd)
{
    std::vector<Server>::iterator fin;
    std::vector<Server>::iterator itr = sudo_apt.begin();
    for (; itr != sudo_apt.end(); itr++)
    {
        std::vector<Client *>::iterator itrs = itr->sudo_client.begin();
        for (; itrs != itr->sudo_client.end(); itrs++)
        {
            if (fd == (*itrs)->fd)
                fin = itr;
        }
    }
    return fin->index;
}

int checkKeepAlive(std::string &buff)
{
    size_t find = buff.find("Connection: keep-alive");
    if(find != buff.npos)
        return(1);
    return(0);
}

int WaitForFullRequest(std::string& buff)
{
    std::string substringToFind = "\r\n\r\n";

    size_t found = buff.find(substringToFind);

    if (found != std::string::npos)
    {
        std::string STR = buff.substr(0, found);

        size_t index = buff.find('\n');
        if (index == std::string::npos)
            return (0);

        std::string http = buff.substr(0, index - 1);
        std::vector<std::string> vec = ft_split(http, " \n\r\t");

        if(vec.size() == 3)
        {
            if (*vec.begin() == "GET" || *vec.begin() == "DELETE")
                return 1;
            else if (*vec.begin() == "POST")
            {
                size_t second = buff.find("Content-Length:");
                if (second != std::string::npos)
                {
                    second += 15;
                    size_t end = buff.find('\n', second);
                    if (end != std::string::npos)
                    {
                        std::string val = buff.substr(second, end - second);
                        int contentLength = std::atoi(val.c_str());

                        if (buff.size() >= found + substringToFind.size() + contentLength)
                            return 1;
                        else
                            return 0;
                    }
                }
                else if (buff.find("Transfer-Encoding: chunked") != std::string::npos)
                {
                    if (buff.find("0\r\n\r\n", found) != std::string::npos)
                        return 1;
                    else
                        return 0;
                }
                else if (buff.find("Content-Type: multipart/form-data") != std::string::npos)
                {
                    size_t boundaryStart = buff.find("boundary=");
                    if (boundaryStart != std::string::npos)
                    {
                        boundaryStart += 9;
                        size_t boundaryEnd = buff.find('\n', boundaryStart);
                        if (boundaryEnd != std::string::npos)
                        {
                            std::string boundary = buff.substr(boundaryStart, boundaryEnd - boundaryStart - 1);
                            std::string endBoundary = "--" + boundary + "--";
                            size_t endBoundaryPos = buff.find(endBoundary, found);
                            if (endBoundaryPos != std::string::npos)
                            {
                                size_t nextBoundaryPos = buff.find("--" + boundary, found);
                                if (nextBoundaryPos == std::string::npos || nextBoundaryPos >= endBoundaryPos)
                                    return 1;
                            }
                        }
                    }
                }
            }
        }
        else
            return 0;
    }
    return 0;
}


bool found_it(int fd, std::vector<class Server> &vec_serve)
{
    for(size_t y = 0; y < vec_serve.size(); y++)
    {
        if (vec_serve[y].fd == fd)
            return true;
    }
    return false;
}

int IoMultiplexing::StartTheMatrix(Parsing &ps)
{
    IoMultiplexing re;
    Request rq;

    rq.Server = ps;

    for (size_t i = 1; i <= ps.getServersNumber(); i++)
    {
        std::string str = ps.getServerDataSingle(i, "listen");
        std::vector<std::string> it = ft_split(str, ':');
        Server qw(std::atoi(it[1].c_str()), it[0]);
        re.sudo_apt.push_back(qw);
    }
    char buffer[50000];
    size_t ll = re.sudo_apt.size();
    for (size_t i = 0; i < ll; i++)
    {
        re.sudo_apt[i].start();
        struct pollfd tmp;
        tmp.fd = re.sudo_apt[i].serversocket;
        tmp.events = POLLIN;
        net.push_back(tmp);
    }
    std::string sttrr;
    signal(SIGPIPE, SIG_IGN);
    struct pollfd tmp;
    while (true)
    {
        struct timeval timeout;
        timeout.tv_sec = 5; 
        timeout.tv_usec = 1;
        int timeout_ms = timeout.tv_sec * 1000 + timeout.tv_usec / 1000;
        int ret = poll(net.data(), net.size(), timeout_ms);
        if (ret == -1)
        {
            continue;
        }
        if (ret == 0 || net.size() >= 10000)
        {
            for (size_t yt = re.sudo_apt.size(); yt < net.size(); yt++)
                close(net[yt].fd);
            net.clear();
            for (size_t i = 0; i < re.sudo_apt.size(); i++) 
            {
                tmp.fd = re.sudo_apt[i].fd;
                tmp.events = POLLIN;
                net.push_back(tmp);
            }
        }
        for (size_t j = 0; j < net.size(); j++)
        {
            if (net[j].revents & POLLIN)
            {
                if (found_it(net[j].fd, re.sudo_apt) && net[j].revents & POLLIN)
                {
                    int clientSocket = accept(net[j].fd, NULL, 0);
                    if (clientSocket == -1)
                        break;
                    struct pollfd tmps;
                    tmps.fd = clientSocket;
                    tmps.events = POLLIN;
                    fcntl(clientSocket, F_SETFL, O_NONBLOCK, FD_CLOEXEC);
                    IoMultiplexing::net.push_back(tmps);
                    continue;
                }
                bzero(buffer, 50000);
                int tt = recv(net[j].fd, buffer, 50000, 0);
                if (tt == 0)
                {
                    close(net[j].fd);
                    continue;
                }
                if (tt == -1)
                {
                    perror("webserv: ");
                    continue;
                }
                else
                {
                    std::string bu(buffer, tt);
                    re.request_msg[net[j].fd].first += bu;
                    bu.clear();
                    if ((WaitForFullRequest(re.request_msg[net[j].fd].first) == 1))
                    {
                        std::cout << "-------------------------------------------------------" << std::endl;
                        std::cout << re.request_msg[net[j].fd].first << std::endl;
                        re.request_msg[net[j].fd].second = rq.InitRequest(re.request_msg[net[j].fd].first, net[j].fd, 1, ps);
                        re.request_msg[net[j].fd].first.clear();
                        net[j].events = POLLOUT;
                        std::cout << "-------------------------------------------------------" << std::endl;
                    }
                    continue;
                }
            }
            else if (net[j].revents & POLLOUT)
            {
                // rq.RequestIsDone  request is done and the response is ready
                // rq.KeepAlive // if true the request is of type keep alive else its close
                usleep(100);
                if(rq.SendFile)//send file with big size
                {
                    //rq.ResponseHeaders  + 

                    //rq.RequestPath
                }
                else//send normal request
                {
                    send(net[j].fd, re.request_msg[net[j].fd].second.c_str(), std::min((size_t) 50000, re.request_msg[net[j].fd].second.length()), 0);    
                    re.request_msg[net[j].fd].second = re.request_msg[net[j].fd].second.substr(re.request_msg[net[j].fd].second.length() < 50000 ? re.request_msg[net[j].fd].second.length() : 50000);
                    if (re.request_msg[net[j].fd].second.size() == 0)
                        net[j].events = POLLIN;
                }
                continue;
            }
        }
    }
}
