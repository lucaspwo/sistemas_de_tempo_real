//
//  servidor5.cpp  - Servidor utilizando protocolo UDP
//  
//
//  Created by Luiz Affonso on 29/11/2020.
//
//

#include "servidor5.hpp"


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
    unsigned int server_len;
    socklen_t client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    
    unsigned short porta = 9734;
    
   
    if ( (server_sockfd = socket(AF_INET, SOCK_DGRAM, 0) )  < 0  )  // cria um novo socket
    {
        printf(" Houve erro na ebertura do socket ");
        exit(1);
    }
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(porta);
    
    
    server_len = sizeof(server_address);
    
    if(  bind(server_sockfd, (struct sockaddr *) &server_address, server_len) < 0 )
    {
        perror("Houve error no Bind");
        exit(1);
    }
    
    
    //listen(server_sockfd, 5);  // No UDP não tem listen()
    while(1){
        char vetor_ch[4];
        
        printf("Servidor esperando ...\n");

        // No UDP não tem accept()
        //client_sockfd = accept(server_sockfd, (struct sockaddr *) &client_address, &client_len);
        
        client_len = sizeof(client_address);
        if(recvfrom(server_sockfd, vetor_ch, sizeof(vetor_ch),0,
                    (struct sockaddr *) &client_address, &client_len) < 0 )
        {
            perror(" erro no RECVFROM( )");
            exit(1);
        }
        for(int i =0; i<4;i++) {
            vetor_ch[i]++;
        }
        sendto(server_sockfd, vetor_ch, sizeof(vetor_ch),0,(struct sockaddr *) &client_address,sizeof(struct sockaddr));
        // close(server_sockfd);
        
    }
}
