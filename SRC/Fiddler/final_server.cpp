#include "../../includes/Server.hpp"

int Server::nbr_srv = 0;

Server::Server(int port, std::string    ip)
{
    this->ip = ip;
    this->port = port;
};

void Server::start()
{
    nbr_srv++;
    index = 0;
    this->serversocket = socket(AF_INET, SOCK_STREAM, 0);
    // std::cout << "socket created " << serversocket << std::endl;
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
    // std::cout << "bind to " << port << std::endl;
    fcntl(this->serversocket, F_SETFL, O_NONBLOCK);
    listen(this->serversocket, 1000);
    // std::cout << "listen to ... " << serversocket << std::endl;
    index = nbr_srv;
    // std::cout << "index >>  " << index << std::endl;
    // std::cout << "nbr_srv >>  " << nbr_srv << std::endl;
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

int   IoMultiplexing::checkServer(int fd)
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
    // std::cout << "fin->index    " << fin->index << std::endl;
    return fin->index;
}

int WaitForFullRequest(std::string buff)
{
    std::string substringToFind = "\r\n\r\n";

    size_t found = buff.find(substringToFind);

    if (found != std::string::npos) {
        return true;
    } else {
        return false;
    }
}

int IoMultiplexing::StartTheMatrix(Parsing &ps)
{
    IoMultiplexing re;
    Request     rq;

    rq.Server = ps;

    for (size_t i = 1; i <= ps.getServersNumber(); i++)
    {
        std::string str = ps.getServerDataSingle(i, "listen");
        std::vector<std::string>  it = ft_split(str, ':');
        Server qw(std::atoi(it[1].c_str()), it[0]);
        // std::cout << "Port|" << qw.port << "|ip|" << qw.ip << std::endl;
        re.sudo_apt.push_back(qw);
    }
    char buffer[3001];
    size_t  ll = re.sudo_apt.size();
    // std::cout << "qwertyui     dsudds   " << ll << std::endl;
    for (size_t i = 0; i < ll; i++)
    {
        re.sudo_apt[i].start();
        struct pollfd tmp;
        tmp.fd = re.sudo_apt[i].serversocket;
        tmp.events = POLLIN;
        net.push_back(tmp);
        // std::cout << re.sudo_apt[i].index << std::endl;
    }
    std::string sttrr;
    signal(SIGPIPE, SIG_IGN);
    while(true)
    {
        int ret = poll(net.data(), net.size(), 0);
        for (size_t j = 0; j < net.size() && ret; j++)
        {
                if (re.isServer(net[j].fd) && net[j].revents & POLLIN)
                {
                    re.acceptNewClient(net[j].fd);
                    continue;
                }
                else if (j >= (size_t)Server::nbr_srv)
                {
                    if (net[j].revents & POLLIN)
                    {
                        bzero(buffer, 3000);
                        int tt = recv(net[j].fd, buffer, 1, 0);
                        if (tt == -1)
                        {
                            perror("webserv: ");
                            continue;
                        }
                        if (tt == 0)
                            close(net[j].fd);
                        else
                        {
                            std::string bu(buffer, tt);
                            re.request_msg[net[j].fd] += bu;
                            bu.clear();
                        }
                        if ((WaitForFullRequest(re.request_msg[net[j].fd]) == true))
                        {
                            std::cerr << re.request_msg[net[j].fd];
                            // int ar =   checkServer(net[j].fd);
                            // std::cout << "yyy  " << ar << std::endl;
                            rq.InitRequest(re.request_msg[net[j].fd], net[j].fd, 1, ps);
                            re.request_msg[net[j].fd].clear();
                            net[j].events = POLLOUT;
                            net[j].revents = 0;
                        }
                        continue;
                    }
                    else if (net[j].revents & POLLOUT)//----------------------SEND REQUEST-----------------------
                    {
                        const char *response = rq.ResponseHeaders.c_str();
                        send(net[j].fd, response, strlen(response), 0);
                        
                        if(rq.ResponseBody.size())
                        {
                            const char *message = rq.ResponseBody.c_str();
                            send(net[j].fd, message, strlen(message), 0);
                        }

                        net[j].events = POLLIN;
                        std::cout << "----------------------END OF RESPONSE---------------------- "<< std::endl;
                        // exit(1);
                    }
                //     // if (net[j].revents & POLLERR | POLLHUP)
                //     // {
                //     //     //close clien and erase it 
                //     // }
                }
                
            // ret--;
        }
    }
}