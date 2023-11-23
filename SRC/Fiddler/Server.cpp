#include "../../includes/Request.hpp"

int    Request::createServer(Webserv &webserv)
{
	Server = webserv;
    
    int serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket == -1)
        return(std::cerr << "Failed to create socket." << std::endl, 1);

    int optionValue = 1;
    setsockopt(serverSocket, SOL_SOCKET, SO_REUSEADDR, &optionValue, sizeof(optionValue));

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

        ssize_t lenght = 0;
        if(strlen(buffer))
        {
            ServerIndex = 1;
            statusCode = 200;
            SendFile = false;
            this->getRequest(buffer);
            std::cout << "StatusCode: " << statusCode << std::endl;
            if(SendFile)
            {
	            std::string str, fileName = "/Users/eamghar/Desktop/Webserv/SRC/Cheesy/EXTRA/send";
	            ResponseBody.clear();

                std::ifstream rd(fileName);
                if (!rd.is_open())
                {
                    std::cerr << "Error Unable to open the file" << std::endl;
                    statusCode = 404;
                }
                else
                {
                    lenght = 0;
                    str.clear();
                    while (std::getline(rd, str))
                    {
                        lenght += str.size();
                        // ResponseBody += str;
                    }

                    rd.close();
                    // remove(fileName.c_str());
                }
            }
            GenerateResponse();
        }
        else
            continue;
        // std::cout << "--------------------START OF HEADER-----------------------" << std::endl;
        // std::cout << ResponseHeaders << std::endl;
        // std::cout << "--------------------START OF BODY-----------------------" << std::endl;
        // // std::cout << ResponseBody << std::endl;
        // std::cout << "--------------------END OF BODY-----------------------" << std::endl;


        // Send a response back to the client

        ssize_t bytesSent = send(clientSocket, ResponseHeaders.c_str(), strlen(ResponseHeaders.c_str()), 0);
        if (bytesSent == -1)
            return(std::cerr << "Error sending response." << std::endl, 1);


        std::string str, fileName = "/Users/eamghar/Desktop/Webserv/SRC/Cheesy/EXTRA/send";

        std::ifstream rd(fileName);
        if (!rd.is_open())
        {
            std::cerr << "Error Unable to open the file" << std::endl;
            statusCode = 404;
        }
        else
        {
            bytesSent = 0;
            while (lenght >= 0)
            {
                std::string str;
                ssize_t i = 0;
                ResponseBody.clear();
                for (; i < MEGA && std::getline(rd, str); i++)
                {
                    ResponseBody += str;
                    i += str.size();
                    // std::cout << "I SIZE: " << i << std::endl;
                }
                bytesSent += send(clientSocket, ResponseBody.c_str(), strlen(ResponseBody.c_str()), 0);
                if (bytesSent == -1)
                    return(std::cerr << "Error sending response." << std::endl, 1);
                lenght -= bytesSent;
            }
        }

        // Close the client socket
        close(clientSocket);
    }

    // Close the server socket
    close(serverSocket);
    return 0;
}