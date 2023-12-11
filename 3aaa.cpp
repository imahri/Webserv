#include <iostream>
#include <cstring>
#include <ifaddrs.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    struct ifaddrs *ifAddrStruct = NULL;
    struct ifaddrs *ifa = NULL;
    void *addrPtr = NULL;


    if (getifaddrs(&ifAddrStruct) == -1) {
        std::cerr << "Error getting network interface information" << std::endl;
        return -1;
    }

    // Iterate through the list of interfaces
    for (ifa = ifAddrStruct; ifa != NULL; ifa = ifa->ifa_next) {
        if (ifa->ifa_addr == NULL) {
            continue;
        }

        // Check for IPv4 address and exclude loopback
        if (ifa->ifa_addr->sa_family == AF_INET &&
            strcmp(ifa->ifa_name, "lo0") != 0) {
            addrPtr = &((struct sockaddr_in *)ifa->ifa_addr)->sin_addr;
            char addrBuf[INET_ADDRSTRLEN];
            inet_ntop(AF_INET, addrPtr, addrBuf, INET_ADDRSTRLEN);
            std::cout << "IP Address: " << addrBuf << std::endl;
            break; // Stop after the first non-loopback IPv4 address
        }
    }
    freeifaddrs(ifAddrStruct);

    return 0;
}
