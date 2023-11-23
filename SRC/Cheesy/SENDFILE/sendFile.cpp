#include "../../../includes/Request.hpp"

size_t ft_strlen(char *str)
{
    int     i = 0;

    if(!str || !str[i])
        return(1);
    while (str[i])
        i++;
    return(i);
}

int Request::FillResponseBodyFromFile(int clientSocket)
{
    std::ifstream file(RequestPath, std::ios::binary);
    if (!file)
        return (std::cerr << "Failed to open the file." << std::endl, 1);

    int bufferSize = 50000;
    char* buffer = new char[bufferSize + 1];
    ssize_t bytesSent;

    file.seekg(offset);

    file.read(buffer, bufferSize);
    offset += file.tellg();
    
    std::cout << "-------------------------------BUFFER---------------------------" << std::endl;
    std::cout << buffer << std::endl;

    bytesSent = send(clientSocket, ResponseBody.c_str(), ResponseBody.size(), 0);
    if (bytesSent == -1)
        return(std::cerr << "Error sending Body Response." << std::endl, 1);

    if (file.eof())
        ClientIsDone = true;

    file.close();
    delete[] buffer;
    return 0;
}