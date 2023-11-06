/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: imahri <imahri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 13:42:21 by imahri            #+#    #+#             */
/*   Updated: 2023/11/01 11:48:11 by imahri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


// #include <csdef>
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

   int opt = 1;
//    setsockopt(server_socket,SOL_SOCKET, SO_REUSEADDR,&opt, (opt));
   n = bind(server_socket, (struct sockaddr*)&server_addr,sizeof(server_addr));
   if (n < 0)
   {
        perror("[-]Bind error");
        exit (1);
   }
   printf("[+]Bind to the port number: %d\n",port);
   listen(server_socket, 5);
   printf("Listening...\n");
   while (1) {
   
        printf("XXXX\n");
        client_socket = accept(server_socket,NULL, 0);
        printf(">>CLIENT %d \n", client_socket);
        printf("[+]Client connected.\n");
   }
   
    return 0;
}