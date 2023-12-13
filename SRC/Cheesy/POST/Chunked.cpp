#include "../../../includes/Request.hpp"

int     Request::parseChuncked()
{
    std::string requestBody = body;
    std::istringstream iss(requestBody);
    std::ostringstream oss;
    
    std::string name = URI.substr(1, URI.size());
    if(name.length() == 0)
        return(statusCode = 400, 1);

    std::string filename = Loc.upload_dir + name;
    std::ofstream file(filename.c_str(), std::ios::out | std::ios::binary);
    if(file.is_open() == false)
        return(statusCode = 500, 1);

    std::string line;
    while (std::getline(iss, line))
    {
        if (line.empty())
            break;

        size_t semicolonPos = line.find(';');
        if (semicolonPos != std::string::npos)
            line = line.substr(0, semicolonPos);

        size_t chunkSize = CovertHexaToDecimal(line);

        std::string chunkData(chunkSize, '\0');
        iss.read(&chunkData[0], chunkSize);
        oss << chunkData;

        std::getline(iss, line);
    }

    std::string str =  oss.str();
    file << str;

    return (0);
}
