#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 8084
#define BUFFER_SIZE 1024

int main(){
int sock,new_sock;
struct sockaddr_in address;
int addrlen=sizeof(address);
char buffer[BUFFER_SIZE]={0};
int expected_frame=0;

if ((sock=socket(AF_INET,SOCK_STREAM,0))==0){
    perror("socket failed");
    exit(EXIT_FAILURE);
}

address.sin_family=AF_INET;
address.sin_addr.s_addr=INADDR_ANY;
address.sin_port=htons(PORT);

if(bind(sock,(struct sockaddr *)&address,sizeof(address))<0){
    perror("Bind failed");
    close(sock);
    exit(EXIT_FAILURE);
}
if(listen(sock,3)<0){
    perror("listen failed");
    close(sock);
    exit(EXIT_FAILURE);

}
printf("receiver: waiting for connection\n");

if((new_sock=accept(sock,(struct sockaddr*)&address,(socklen_t *)&addrlen))<0){
    perror("accept failed");
    close(sock);
    exit(EXIT_FAILURE);
}

printf("receiver: connection established\n");

while(1){
    memset(buffer,0,BUFFER_SIZE);
    read(new_sock,buffer,BUFFER_SIZE);
    int received_frame=atoi(buffer);
    printf("receiver: received frame %d\n",received_frame);

    if(received_frame==expected_frame){
        printf("receiver:sending acknowledgment for frame %d\n",received_frame);
        sprintf(buffer,"ACK%d",received_frame);
        expected_frame=1-expected_frame;

    }else{
        printf("Receiver:Duplicate frame %d.resending last acknowledgment\n",received_frame);
        sprintf(buffer,"ACK%d",1-expected_frame);

    }
    send(new_Sock,buffer,strlen(buffer),0);



}
close(new_sock);
close(sock);
return 0;
}