#include "../../includes/Request.hpp"

// int    Request::createServer(Webserv &webserv)
// {
// 	Server = webserv;
    
//     const char *ip = "0.0.0.0";
//     int port = 3000;
//     int serverSocket;
//     int clientSocket;
//     struct sockaddr_in serverAddr;
//     int n;

//     serverSocket = socket(AF_INET, SOCK_STREAM, 0);
//     if (serverSocket < 0) {
//         perror("[-] Socket error");
//         exit(1);
//     }

//     std::cout << "[+] Server socket created" << std::endl;

//     bzero(&serverAddr, sizeof(serverAddr));
//     serverAddr.sin_family = AF_INET;
//     serverAddr.sin_port = htons(port);
//     serverAddr.sin_addr.s_addr = inet_addr(ip);
//     serverAddr.sin_zero[7] = '\0';

//     while (true) {
//         n = bind(serverSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr));
//         if (n < 0) {
//             continue;
//         } else {
//             break;
//         }
//     }

//     std::cout << "[+] Bound to port number: " << port << std::endl;
//     listen(serverSocket, 1);
//     std::cout << "Listening..." << std::endl;

//     while (true)
//     {
//         clientSocket = accept(serverSocket, NULL, 0);

//         // Read the request from the client
//         char buffer[1024];
//         memset(&buffer, 0, sizeof(buffer));
//         ssize_t bytesRead = read(clientSocket, &buffer, sizeof(buffer) - 1);
//         if (bytesRead == -1)
//             return(std::cerr <<"Error reading request." << std::endl, 1);
    
//         //Print the received request
//         std::cout << "Received request:\n" << buffer << std::endl;

//         if(strlen(buffer))
//         {
//             statusCode = 0;
//             this->getRequest(buffer);
//             std::cout << "StatusCode: " << statusCode << std::endl;
//         }
//         else
//             continue;

//         const char *response = "HTTP/1.1 200 OK\nContent-Length: 10\nContent-Type: text/plain\r\n";
//         const char *message = "FARMLIYA";

//         send(clientSocket, response, strlen(response), 0);
//         send(clientSocket, message, strlen(message), 0);

//         std::cout << ">> CLIENT: " << clientSocket << std::endl;
//         std::cout << "[+] Client connected" << std::endl;
//     }
//     close(serverSocket);
//     close(clientSocket);
//     return 0;
// }


int    Request::createServer(Webserv &webserv)
{
	Server = webserv;
    

    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
        return(std::cerr << "Failed to create socket." << std::endl, 1);

    // Set up server address
    sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(8080);  // Use the desired port number
    serverAddress.sin_addr.s_addr = INADDR_ANY;

    // Bind the socket to the server address
    if (bind(serverSocket, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) == -1)
        return(std::cerr << "Failed to bind socket." << std::endl, 1);

    // Start listening for incoming connections
    if (listen(serverSocket, 5) == -1)
        return(std::cerr <<"Error while listening." << std::endl, 1);

    std::cout << "Server started. Listening on port 8080..." << std::endl;

    while (true)
    {
        // Accept a client connection
        sockaddr_in clientAddress;
        socklen_t clientAddressLength = sizeof(clientAddress);
        int clientSocket = accept(serverSocket, (struct sockaddr *) &clientAddress, &clientAddressLength);
        if (clientSocket == -1)
            return(std::cerr <<"Error accepting client connection." << std::endl, 1);

        // Read the request from the client
        char buffer[1024];
        memset(&buffer, 0, sizeof(buffer));
        ssize_t bytesRead = read(clientSocket, &buffer, sizeof(buffer) - 1);
        if (bytesRead == -1)
            return(std::cerr <<"Error reading request." << std::endl, 1);
    
        //Print the received request
        std::cout << "--------------------START OF REQUEST-----------------------" << std::endl;
        std::cout << "Received request:\n" << buffer << std::endl;
        std::cout << "--------------------START PARSING REQUEST-----------------------" << std::endl;

        if(strlen(buffer))
        {
            ServerIndex = 1;
            statusCode = 0;
            this->getRequest(buffer);
            std::cout << "StatusCode: " << statusCode << std::endl;
        }
        else
            continue;
        std::cout << "--------------------END OF REQUEST-----------------------" << std::endl;
        std::cout << "--------------------START OF HEADER-----------------------" << std::endl;
        std::cout << ResponseHeaders << std::endl;
        std::cout << "--------------------END OF HEADER-----------------------" << std::endl;
        std::cout << "--------------------START OF BODY-----------------------" << std::endl;
        std::cout << ResponseBody << std::endl;
        std::cout << "--------------------END OF BODY-----------------------" << std::endl;


        // Send a response back to the client
        // const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<h1>Hello, World!</h1>";
        ssize_t bytesSent = send(clientSocket, ResponseHeaders.c_str(), strlen(ResponseHeaders.c_str()), 0);
        if (bytesSent == -1)
            return(std::cerr << "Error sending response." << std::endl, 1);
        bytesSent = send(clientSocket, ResponseBody.c_str(), strlen(ResponseBody.c_str()), 0);
        if (bytesSent == -1)
            return(std::cerr << "Error sending response." << std::endl, 1);
        // Close the client socket
        close(clientSocket);
    }

    // Close the server socket
    close(serverSocket);
    return 0;
}