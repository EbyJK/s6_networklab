#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<arpa/inet.h>

#define PORT 8083
#define BUFFER_SIZE 1024
#define SERVER_IP "127.0.0.1"
int main(){
int sock;
struct sockaddr_in server_addr;
char buffer[BUFFER_SIZE]={0};
socklen_t addr_len=sizeof(server_addr);

if
((sock=socket(AF_INET,SOCK_DGRAM,0))==
-1)
{
perror("socket creation failed");
exit(EXIT_FAILURE);
}
server_addr.sin_family=AF_INET;
server_addr.sin_port=htons(PORT);

if(inet_pton(AF_INET,SERVER_IP,&server_ad
dr.sin_addr)<=0){
perror("Invalid address or address not
supported");
exit(EXIT_FAILURE);

}
printf("ready to send messages to udp
server\n");
while(1){

memset(buffer,0,sizeof(buffer));
printf("enter message to send to server
(type 'exit' to quit):");
fgets(buffer,sizeof(buffer),stdin);
buffer[strcspn(buffer,"\n")]=0;
sendto(sock,buffer,strlen(buffer),0,(struct
sockaddr *)&server_addr,addr_len);
printf("message send to server\n");
if(strcmp(buffer,"exit")==0){
printf("exitting communication..\n");
break;
}
memset(buffer,0,sizeof(buffer));
int
valread=recvfrom(sock,buffer,sizeof(buffer),0,(s
truct sockaddr *)&server_addr,&addr_len);
if(valread<=0){
printf("server not communicating or error
occurred\n");
break;
}
printf("messsage from
server:%s\n",buffer);

}
close(sock);
return 0;
//no connect part
// additional parameeters for send and recv functions

}