//
//  cliente5.cpp  - Cliente utilizando protocolo UDP
//  
//
//  Created by Luiz Affonso on 29/11/2020.
//
//

#include "cliente5.hpp"



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
    socklen_t len_recv;
    struct sockaddr_in address;
    int result;
    char vetor_ch[4] = {'A','B','C','D'};
    
    unsigned short porta = 9734;
    
    sockfd  = socket(AF_INET, SOCK_DGRAM,0);  // criacao do socket
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(porta);
    
    len = sizeof(address);
    len_recv = sizeof(address);
    
    sendto(sockfd,  vetor_ch,sizeof(vetor_ch),0,(struct sockaddr *) &address, len);
    recvfrom(sockfd, vetor_ch,sizeof(vetor_ch),0,(struct sockaddr *) &address,&len_recv);

    
    printf( "Caracteres vindos do servidor = %c %c %c %c\n",vetor_ch[0],vetor_ch[1],vetor_ch[2],vetor_ch[3]);
    close(sockfd);
    exit(0);
}
