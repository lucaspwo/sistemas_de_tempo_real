//
//  servidor4.cpp  --> escreve um estrutura
//  
//
//  Created by Luiz Affonso on 29/11/2020.
//
//

#include "servidor4.hpp"


#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main( )
{
    int server_sockfd, client_sockfd;
    unsigned int server_len, client_len;
    struct sockaddr_in server_address;
    struct sockaddr_in client_address;
    
    
    server_sockfd = socket(AF_INET, SOCK_STREAM, 0);  // cria um novo socket
    
    server_address.sin_family = AF_INET;
    //server_address.sin_addr.s_addr = inet_addr("127.0.0.1"); // só clientes locais
    server_address.sin_addr.s_addr  = INADDR_ANY;  // qualquer cliente
    server_address.sin_port = 9734;
    
    
    server_len = sizeof(server_address);
    bind(server_sockfd, (struct sockaddr *) &server_address, server_len);
    
    listen(server_sockfd, 5);
    while(1) {
        struct dado {
            int idade;
            char nome[34];
        };
        
        dado aluno;
        aluno.idade = 38;
        strcpy(aluno.nome, "Jose Silva");
        
        printf("Servidor esperando ...\n");
        client_sockfd = accept(server_sockfd, (struct sockaddr *) &client_address, &client_len);
        
        write(client_sockfd, &aluno, sizeof(aluno));
        close(client_sockfd);
    }
}
