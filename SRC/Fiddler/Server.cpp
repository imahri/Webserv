#include "../../includes/Request.hpp"

int    Request::createServer(Webserv &webserv)
{
	Server = webserv;
    
    const char *ip = "0.0.0.0";
    int port = 3000;
    int serverSocket;
    int clientSocket;
    struct sockaddr_in serverAddr;
    int n;

    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0) {
        perror("[-] Socket error");
        exit(1);
    }

    std::cout << "[+] Server socket created" << std::endl;

    bzero(&serverAddr, sizeof(serverAddr));
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    serverAddr.sin_addr.s_addr = inet_addr(ip);
    serverAddr.sin_zero[7] = '\0';

    while (true) {
        n = bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
        if (n < 0) {
            continue;
        } else {
            break;
        }
    }

    std::cout << "[+] Bound to port number: " << port << std::endl;
    listen(serverSocket, 1);
    std::cout << "Listening..." << std::endl;

    while (true)
    {
        clientSocket = accept(serverSocket, NULL, 0);

        // Read the request from the client
        char buffer[1024];
        memset(&buffer, 0, sizeof(buffer));
        ssize_t bytesRead = read(clientSocket, &buffer, sizeof(buffer) - 1);
        if (bytesRead == -1)
            return(std::cerr <<"Error reading request." << std::endl, 1);
    
        //Print the received request
        std::cout << "Received request:\n" << buffer << std::endl;

        if(strlen(buffer))
        {
            statusCode = 0;
            this->getRequest(buffer);
            std::cout << "StatusCode: " << statusCode << std::endl;
        }
        else
            continue;

        const char *response = "HTTP/1.1 200 OK\nContent-Length: 10\nContent-Type: text/plain\n\n";
        const char *message = "FARMLIYA";

        send(clientSocket, response, strlen(response), 0);
        send(clientSocket, message, strlen(message), 0);

        std::cout << ">> CLIENT: " << clientSocket << std::endl;
        std::cout << "[+] Client connected" << std::endl;
    }
    close(serverSocket);
    close(clientSocket);
    return 0;
}
