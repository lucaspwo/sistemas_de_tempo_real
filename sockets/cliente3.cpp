//
//  cliente3.cpp  --> Lê um vetor de caracter
//  
//
//  Created by Luiz Affonso on 29/11/2020.
//
//

#include "cliente3.hpp"


#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>

int main( )
{
    int sockfd;
    int len;
    struct sockaddr_in address;
    int result;
    char vetor_ch[4] = {'A','B','C','D'};
    
    sockfd  = socket(AF_INET, SOCK_STREAM,0);  // criacao do socket
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = 9734;

    
    len = sizeof(address);
    
    result = connect(sockfd, (struct sockaddr *) &address, len);
    
    if (result == -1)
    {
        perror ("Houve erro no cliente");
        exit(1);
    }
    
    send(sockfd,  vetor_ch,sizeof(vetor_ch),0);
    recv(sockfd, vetor_ch,sizeof(vetor_ch),0);
    //write(sockfd,  vetor_ch,sizeof(vetor_ch));
    //read(sockfd, vetor_ch,sizeof(vetor_ch));
    
    printf( "Caracteres vindos do servidor = %c %c %c %c\n",vetor_ch[0],vetor_ch[1],vetor_ch[2],vetor_ch[3]);
    close(sockfd);
    exit(0);
}
