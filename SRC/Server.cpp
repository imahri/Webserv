#include "../includes/Request.hpp"

int    Request::createServer()
{
    // Create a socket
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
        std::cout << "Received request:\n" << buffer << std::endl;

        if(strlen(buffer))
            this->getRequest(buffer);
        else
            continue;

        // Send a response back to the client
        const char *response = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<h1>Hello, World!</h1>";
        ssize_t bytesSent = send(clientSocket, response, strlen(response), 0);
        if (bytesSent == -1)
            return(std::cerr << "Error sending response." << std::endl, 1);

        // Close the client socket
        close(clientSocket);
    }

    // Close the server socket
    close(serverSocket);
    return(0);
}
