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
    char* buffer = new char[bufferSize];
    ssize_t bytesSent;

    file.seekg(offset);
    file.read(buffer, bufferSize);
    int a = file.tellg();

    bytesSent = send(clientSocket, buffer, a, 0);
    if (bytesSent == -1)
        return(std::cerr << "Error sending Body Response." << std::endl, 1);

    offset += bytesSent;

    if (file.eof())
        ClientIsDone = true;

    file.close();
    delete[] buffer;
    return 0;
}
