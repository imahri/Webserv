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

        if(strlen(buffer))
        {
            offset = 0;
            RequestIsDone = false;
            ClientIsDone = false;
            PathToSaveFile = "/Users/eamghar/Desktop/send";
            ResponseHeaders.clear();
            ResponseBody.clear();
            this->getRequest(buffer);
            std::cout << "StatusCode: " << statusCode << std::endl;
            GenerateResponse();
        }
        else
            continue;
        std::cout << "--------------------START OF HEADER-----------------------" << std::endl;
        std::cout << ResponseHeaders << std::endl;
        std::cout << "--------------------START OF BODY-----------------------" << std::endl;
        // std::cout << ResponseBody << std::endl;
        std::cout << "--------------------END OF BODY-----------------------" << std::endl;


        // Send a response back to the client

        ssize_t bytesSent = send(clientSocket, ResponseHeaders.c_str(), strlen(ResponseHeaders.c_str()), 0);
        if (bytesSent == -1)
            return(std::cerr << "Error sending Header Response." << std::endl, 1);

        if(SendFile)
        {
            offset = 0;
            std::ifstream file(RequestPath, std::ios::binary);
            if (!file)
                return (std::cerr << "Failed to open the file." << std::endl, 1);
            file.seekg(0, std::ios::end);
            FileSize = file.tellg();
            file.close();
            std::cout << "FILESIZE: " << FileSize << std::endl;
            while (ClientIsDone == false)
                if(FillResponseBodyFromFile(clientSocket))
                    break;
        }
        else
        {
            std::cout << "-------------->>>>>>>>>>>>>>>>>>>>>>>>>>>.-----------------------------" << std::endl;
            bytesSent = send(clientSocket, ResponseBody.c_str(), strlen(ResponseBody.c_str()), 0);
            if (bytesSent == -1)
                return(std::cerr << "Error sending Body Response." << std::endl, 1);
        }
        // Close the client socket
        close(clientSocket);
    }

    // Close the server socket
    close(serverSocket);
    return 0;
}
