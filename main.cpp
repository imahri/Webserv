#include "Request.hpp"

std::vector<std::string> split(const std::string& str, char delimiter) {
    std::vector<std::string> tokens;
    std::istringstream iss(str);
    std::string token;
    while (std::getline(iss, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

std::vector<Location> parseConfigFile(const std::string& filename) {
    std::vector<Location> locations;

    std::ifstream configFile(filename.c_str());
    if (!configFile.is_open()) {
        std::cerr << "Failed to open config file: " << filename << std::endl;
        return locations;
    }

    std::string line;
    Location currentLocation;

    while (std::getline(configFile, line)) {
        if (line.empty()) {
            if (!currentLocation.path.empty()) {
                locations.push_back(currentLocation);
                currentLocation = Location();
            }
        } else {
            std::istringstream iss(line);
            std::string key, value;
            iss >> key >> value;

            if (key == "location") {
                if (!currentLocation.path.empty()) {
                    locations.push_back(currentLocation);
                    currentLocation = Location();
                }
                currentLocation.path = value;
            } else if (key == "root") {
                currentLocation.root = value;
            } else if (key == "methods") {
                std::vector<std::string> methods = split(value, ',');
                for (std::vector<std::string>::iterator it = methods.begin(); it != methods.end(); ++it) {
                    std::string method = *it;
                    method.erase(std::remove(method.begin(), method.end(), ' '), method.end());
                    currentLocation.methods.push_back(method);
                }
            } else if (key == "upload_dir") {
                currentLocation.uploadDir = value;
            } else if (key == "cgi_php") {
                currentLocation.cgiPhp = value;
            } else if (key == "cgi_py") {
                currentLocation.cgiPy = value;
            } else if (key == "redirect") {
                currentLocation.redirect = value;
            }
        }
    }

    if (!currentLocation.path.empty()) {
        locations.push_back(currentLocation);
    }

    configFile.close();

    return locations;
}

int     Request::fillLocations()
{
    locations = parseConfigFile("default.conf");

    // Print the data from each location
    for (std::vector<Location>::const_iterator it = locations.begin(); it != locations.end(); it++)
    {
        const Location& location = *it;
        std::cout << "Path: " << location.path << std::endl;
        std::cout << "Root: " << location.root << std::endl;
        std::cout << "Methods: ";
        for (std::vector<std::string>::const_iterator methodIt = location.methods.begin(); methodIt != location.methods.end(); ++methodIt) {
            std::string method = *methodIt;
            std::cout << method << " ";
        }
        std::cout << std::endl;
        std::cout << "Upload Dir: " << location.uploadDir << std::endl;
        std::cout << "CGI PHP: " << location.cgiPhp << std::endl;
        std::cout << "CGI PY: " << location.cgiPy << std::endl;
        std::cout << "Redirect: " << location.redirect << std::endl;
        std::cout << std::endl;
    }

    return(0);
}

int main()
{
    Request     rq;

    rq.fillLocations();
    if(rq.createServer())
        return(1);

    return 0;
}