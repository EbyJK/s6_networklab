#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8082
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE] = {0};
    
    // Create socket
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    
    // Convert IP address to binary form
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("Invalid address or Address not supported");
        exit(EXIT_FAILURE);
    }

    // Connect to the server
    if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Connection failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    printf("Connected to the server\n");

    // Communication loop
    while (1) {
        // Receive message from the server
        memset(buffer, 0, sizeof(buffer));  // Clear the buffer
        

        

        // Ask the user for a message to send to the server
        printf("Enter message to send to server (type 'exit' to quit): ");
        fgets(buffer, sizeof(buffer), stdin);  // Read message from user
        buffer[strcspn(buffer, "\n")] = 0;  // Remove newline character
send(sock, buffer, strlen(buffer), 0);
 printf("Message sent to server\n");
        // If user types "exit", close the connection
        if (strcmp(buffer, "exit") == 0) {
            printf("Exiting communication...\n");
            break;
        }memset(buffer, 0, sizeof(buffer));

        
        int valread = read(sock, buffer, sizeof(buffer));
        // Print the received message from the server
        printf("Message from server: %s\n", buffer);
        if (valread <= 0) {
            printf("Server disconnected or error occurred.\n");
            break;
        }
        if (strcmp(buffer, "exit") == 0) {
            printf("Exiting communication...\n");
            break;
        }

    }

    // Close the socket
    close(sock);

    return 0;
}

