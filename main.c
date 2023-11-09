/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imahri <imahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:42:21 by imahri            #+#    #+#             */
/*   Updated: 2023/11/09 09:51:54 by imahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// #include <cstddef>
#include <netinet/in.h>
#include <string.h>
#include <stdio.h>
#include <sys/_endian.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <arpa/inet.h>


int main()
{
    char *ip = "127.0.0.1";
   int port = 3000;
   int server_socket;
   int client_socket;
   struct sockaddr_in server_addr;
   socklen_t addr_size;
   char buffer[1024];
   int n;
   server_socket = socket(AF_INET, SOCK_STREAM, 0);
   if (server_socket < 0)
   {
        perror("[-]Socket error");
        exit (1);
   }
   printf("[+]server soket created.\n");
   
   bzero(&server_addr,sizeof(server_addr));
   server_addr.sin_family = AF_INET;
   server_addr.sin_port = htons(port);
//    std::cout <<  <<server_addr.sin_port;
    printf(">> %d \n",server_addr.sin_port);
//    server_addr.sin_addr.s_addr = htons(ip);
    server_addr.sin_addr.s_addr = inet_addr(ip);
    server_addr.sin_zero[7]='\0';
    
//    setsockopt(server_socket,SOL_SOCKET, SO_REUSEADDR,NULL, 0);
   while (1) {
        n = bind(server_socket, (struct sockaddr*)&server_addr,sizeof(server_addr));
        if (n < 0)
            continue;
        else
            break;
   }

   printf("[+]Bind to the port number: %d\n",port);
   listen(server_socket, 5);
   printf("Listening...\n");
   while (1) {
        client_socket = accept(server_socket,NULL, 0);
        // char *res = "HTTP/1.1 200 OK\nContent-Length: 10\nContent-Type: application/octet-stream\n\n";
        char *res = "HTTP/1.1 200 OK\nContent-Length: 10\nContent-Type: text/plain\n\n";
        char *msg = "hacker men";
        send(client_socket,res,strlen(res),0);
        send(client_socket,msg,strlen(msg),0);
        printf(">>CLIENT %d \n", client_socket);
        printf("[+]Client connected.\n");
   }
   
    return 0;
}