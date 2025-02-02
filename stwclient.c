#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 8084
#define BUFFER_SIZE 1024
#define TIMEOUT 5

int main(){
    int sock=0;
    struct sockaddr_in serv_addr;
    char buffer[BUFFER_SIZE]={0};
    int frame=0;

    if((sock=socket(AF_INET,SOCK_STREAM,0))<0){
        perror("socket creation failed\n");
        exit(EXIT_FAILURE);


    }
    serv_addr,sin_family=AF_INET;
    serv_addr.sin_port=htons(PORT);
    
    if(inet_pton(AF_INET,"127.0.0.1",&serv_addr.sin_addr)<=0){
        perror("invalid address/address not supported\n");
        exit(EXIT_FAILURE);
    }
    if(connect(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0){
        perror("connection failed\n");
        close(sock);
        exit(EXIT_FAILURE);

    }
    printf("sender:connected to receiver.\n");
    while(1){
        printf("sender:sending frame %d\n",frame);
        sprintf(buffer,"%d",frame);
        send(sock,buffer,strlen(buffer),0);
    

    }

}