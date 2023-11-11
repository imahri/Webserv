/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imahri <imahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/09 09:55:30 by imahri            #+#    #+#             */
/*   Updated: 2023/11/11 22:41:03 by imahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>


int main() {
    const char *ip = "0.0.0.0";
    int port = 3000;
    int serverSocket;
    int clientSocket;
    struct sockaddr_in serverAddr;
    socklen_t addrSize;
    char buffer[1024];
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

    while (true) {
        clientSocket = accept(serverSocket, NULL, 0);

        const char *response = "HTTP/1.1 200 OK\nContent-Length: 10\nContent-Type: text/plain\n\n";
        const char *message = "hacker men";

        send(clientSocket, response, strlen(response), 0);
        send(clientSocket, message, strlen(message), 0);

        std::cout << ">> CLIENT: " << clientSocket << std::endl;
        std::cout << "[+] Client connected" << std::endl;
    }
    return 0;
}