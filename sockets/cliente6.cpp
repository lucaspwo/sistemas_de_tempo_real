//
//  cliente6.cpp  - Cliente UDP que envia números inteiros inteiror para um servidor UDP
//  
//
//  Created by Luiz Affonso on 29/11/2020.
//
//

#include "cliente6.hpp"

#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

int main( )
{
    int sockfd;
    int len;
    socklen_t len_recv;
    struct sockaddr_in address;
    int result;
    
    
    unsigned short porta = 9734;
    
    sockfd  = socket(AF_INET, SOCK_DGRAM,0);  // criacao do socket
    
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");  // localhost
    // address.sin_addr.s_addr = inet_addr("10.13.127.255"); // broadcast
    address.sin_port = htons(porta);
    
    len = sizeof(address);
    
    for(int i=0;i<30;i++)
    {
        sendto(sockfd, &i,sizeof(i),0,(struct sockaddr *) &address, len);
        sleep(1);
    }
    close(sockfd);
    exit(0);
}
