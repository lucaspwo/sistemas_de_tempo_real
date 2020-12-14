//
//  servidor3.cpp  --> escreve um vertor de carcateres
//  
//
//  Created by Luiz Affonso on 29/11/2020.
//
//

#include "servidor3.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <unistd.h>
#include <stdlib.h>

int main( )
{
    int server_sockfd, client_sockfd;
    unsigned int server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);  // cria um novo socket
    
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_address.sin_port = 9734;
    
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *) &server_address, server_len);
    
    listen(server_sockfd, 5);
    while(1) {
        char vetor_ch[4];
        
        printf("Servidor esperando ...\n");
        client_sockfd = accept(server_sockfd, (struct sockaddr *) &client_address, &client_len);
        
        read(client_sockfd, vetor_ch, sizeof(vetor_ch));
        for(int i =0; i<4;i++) {
            vetor_ch[i]++;
        }
        write(client_sockfd, vetor_ch, sizeof(vetor_ch));
        close(client_sockfd);
    }
}
