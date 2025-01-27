#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<stdlib.h>
#include<arpa/inet.h>
#define PORT 8083
#define BUFFER_SIZE 1024
int main(){
int sock;
struct sockaddr_in
server_addr,client_addr;
socklen_t addr_len=sizeof(client_addr);
char buffer[BUFFER_SIZE]={0};

if((sock=socket(AF_INET,SOCK_DGRAM,0))=
=0){
perror("socket failed");
exit(EXIT_FAILURE);

}
server_addr.sin_family=AF_INET;
server_addr.sin_addr.s_addr=INADDR_ANY;
server_addr.sin_port=htons(PORT);
if(bind(sock,(struct sockaddr
*)&server_addr,sizeof(server_addr))<0){
perror("bind failed");
close(sock);
exit(EXIT_FAILURE);

}
printf("server listening on port
%d..\n",PORT);
while(1){

memset(buffer,0,sizeof(buffer));
int
valread=recvfrom(sock,buffer,sizeof(buffer),0,(s
truct sockaddr *)&client_addr,&addr_len);
if(valread<=0){
printf("client not communicating or error
occurred\n");
break;
}
printf("message from client:
%s\n",buffer);
if(strcmp(buffer,"exit")==0){
printf("client requested to exit\n");
break;
}
printf("enter message to send to client
(type 'exit' to quit):");
fgets(buffer,sizeof(buffer),stdin);
buffer[strcspn(buffer,"\n")]=0;
sendto(sock,buffer,sizeof(buffer),0,(struct
sockaddr *)&client_addr,addr_len);
printf("response to client\n");
if(strcmp(buffer,"exit")==0){
printf("exitting from communication\n");
// server message exit
break;
}

}
close(sock);
return 0;
}