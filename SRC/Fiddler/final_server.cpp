#include "../../includes/Server.hpp"

int Server::nbr_srv = 0;

Server::Server(int port, std::string    ip)
{
    this->ip = ip;
    this->port = port;
};

void Server::start()
{
    this->serversocket = socket(AF_INET, SOCK_STREAM, 0);
    std::cout << "socket created " << serversocket << std::endl;
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
    std::cout << "bind to " << port << std::endl;
    fcntl(this->serversocket, F_SETFL, O_NONBLOCK);
    listen(this->serversocket, 1000);
    std::cout << "listen to ... " << serversocket << std::endl;
    nbr_srv++;
}

int IoMultiplexing::maxfd = 0;
std::vector<struct pollfd> IoMultiplexing::net;

bool    IoMultiplexing::isDoneRequest(char *str)
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

bool    IoMultiplexing::isServer(int fd)
{
    std::vector<Server>::iterator itr = sudo_apt.begin();

    for (; itr != sudo_apt.end(); itr++)
    {
        if (fd == itr->serversocket)
            return true;
    }
    return false;
}

int     IoMultiplexing::foundServer(int fd)
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

void    IoMultiplexing::acceptNewClient(int fd)
{
    int clientSocket = accept(fd, NULL, 0);
    struct pollfd tmp;
    tmp.fd = clientSocket;
    tmp.events = POLLIN | POLLOUT;
    fcntl(clientSocket, F_SETFL, O_NONBLOCK, FD_CLOEXEC);
    IoMultiplexing::net.push_back(tmp);
    int finder = foundServer(fd);
    if (finder != -1)
    {
        Client *cr = new Client(clientSocket);
        sudo_apt[finder].sudo_client.push_back(cr);
    }
}

std::vector<Client *>::iterator    IoMultiplexing::checkClient(int fd)
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

std::vector<Server>::iterator    IoMultiplexing::checkServer(int fd)
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

int IoMultiplexing::StartTheMatrix(Parsing &ps)
{
    IoMultiplexing re;

    for (size_t i = 1; i <= ps.getServersNumber(); i++)
    {
        std::string str = ps.getServerDataSingle(i, "listen");
        std::vector<std::string>  it = ft_split(str, ':');
        Server qw(std::atoi(it[1].c_str()), it[0]);
        re.sudo_apt.push_back(qw);
    }
    std::cout << "--------------------------------" << std::endl;


    char buffer[3001];
    size_t  ll = re.sudo_apt.size();

    for (size_t i = 0; i < ll; i++)
    {
        re.sudo_apt[i].start();
        struct pollfd tmp;
        tmp.fd = re.sudo_apt[i].serversocket;
        tmp.events = POLLIN;
        IoMultiplexing::net.push_back(tmp);
    }
    signal(SIGPIPE, SIG_IGN);
    while(true)
    {
        int ret = poll(IoMultiplexing::net.data(), IoMultiplexing::net.size(), 0);
        for (size_t j = 0; j < IoMultiplexing::net.size() && ret; j++)
        {
                if (re.isServer(IoMultiplexing::net[j].fd) && IoMultiplexing::net[j].revents & POLLIN)
                {
                    re.acceptNewClient(IoMultiplexing::net[j].fd);
                    continue;
                }
                else if (j >= (size_t)Server::nbr_srv){
                
                    if (IoMultiplexing::net[j].revents & POLLIN)
                    {
                        while(1)
                        {
                            bzero(buffer, 3000);
                            int tt = recv(IoMultiplexing::net[j].fd, buffer,3000, 0);
                            std::cout << "===>> " << tt << std::endl;
                            if (tt == 0)
                            {
                                close(IoMultiplexing::net[j].fd);
                            }
                            else if (tt < 0)
                                break;
                            std::cout << buffer << std::endl;
                        }
                        if (re.isDoneRequest(buffer))
                        {
                            // int sta = re.checkClient(IoMultiplexing::net[j].fd);
                            std::cout << "XXXX" << std::endl;
                            IoMultiplexing::net[j].events = POLLOUT;
                            IoMultiplexing::net[j].revents = 0;
                        }
                        continue;
                    }
                    else if (IoMultiplexing::net[j].revents & POLLOUT){
                        // std::cout << IoMultiplexing::net[j].fd << std::endl;
                        //response
                        // if data end
                        const char *response = "HTTP/1.1 200 OK\r\nContent-Length: 10\r\nContent-Type: text/plain\r\n\r\n"; // here start the response send 500000
                        const char *message = "hacker men";
                        send(IoMultiplexing::net[j].fd, response, strlen(response), 0);
                        send(IoMultiplexing::net[j].fd, message, strlen(message), 0);
                        IoMultiplexing::net[j].events = POLLIN;

                    }
                //     // if (IoMultiplexing::net[j].revents & POLLERR | POLLHUP)
                //     // {
                //     //     //close clien and erase it 
                //     // }
                }
                
            // ret--;
        }
    }
    return(0);
}
