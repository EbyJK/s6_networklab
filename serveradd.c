#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8083
#define BUFFER_SIZE 1024

int main() {
    int server_fd, new_socket;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE] = {0};
    char buffer2[BUFFER_SIZE]= {0};
    char buffer3[BUFFER_SIZE]= {0};
    
    // Create socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("Socket failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);
    
    // Bind the socket to the address and port
    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    // Start listening for incoming connections
    if (listen(server_fd, 3) < 0) {
        perror("Listen failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d...\n", PORT);
    
    // Accept incoming connection
    if ((new_socket = accept(server_fd, (struct sockaddr *)&client_addr, &addr_len)) < 0) {
        perror("Accept failed");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("Connection established with client\n");

    // Communication loop
    
        memset(buffer, 0, sizeof(buffer));  // Clear the buffer
	 memset(buffer2, 0, sizeof(buffer2)); 
	  memset(buffer3, 0, sizeof(buffer3)); 
        // Receive message from client
        //int valread = read(new_socket, buffer, sizeof(buffer));
        
      /*  if (valread <= 0) {
            printf("Client disconnected or error occurred.\n");
            break;
        }*/

        // Print the received message
      
        
        int n1,n2, sum;
        n1=read(new_socket,buffer,2);
        n2=read(new_socket,buffer2,3);
        
          printf("Message from client: %s\n", buffer);
            printf("Message from client: %s\n", buffer2);
        
        sum=atoi(buffer)+atoi(buffer2);
        
        
        printf("sum of the number:%d\n" , sum);
        
        
        char s[10];
        sprintf(s,"%d",sum);

        // If client sends "exit", break the loop and close the connection
        if (strcmp(buffer, "exit") == 0) {
            printf("Client requested to exit.\n");
           
        }

        // Send response to client
        printf("Enter message to send to server (type 'exit' to quit): ");
        fgets(buffer, sizeof(buffer), stdin);
        send(new_socket, s, strlen(s), 0);
        printf("Response sent to client\n");
        if (strcmp(buffer, "exit") == 0) {
            printf("Client requested to exit.\n");
           
        }
        
    

    // Close the connection
    close(new_socket);
    close(server_fd);

    return 0;
}


