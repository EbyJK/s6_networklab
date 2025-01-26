#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8082
#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t addr_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE] = {0};

    // Create UDP socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    // Bind the socket to the port
    if (bind(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("Bind failed");
        close(sock);
        exit(EXIT_FAILURE);
    }

    printf("Server listening on port %d (UDP)...\n", PORT);

    // Communication loop
    while (1) {
        memset(buffer, 0, sizeof(buffer));  // Clear the buffer

        // Receive message from client
        int valread = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&client_addr, &addr_len);
        if (valread <= 0) {
            printf("Client disconnected or error occurred.\n");
            break;
        }

        // Print the received message
        printf("Message from client: %s\n", buffer);

        // If client sends "exit", break the loop
        if (strcmp(buffer, "exit") == 0) {
            printf("Client requested to exit.\n");
            break;
        }

        // Send response to client
        printf("Enter message to send to client (type 'exit' to quit): ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;  // Remove newline character
        sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr *)&client_addr, addr_len);
        printf("Response sent to client\n");

        // If server sends "exit", break the loop
        if (strcmp(buffer, "exit") == 0) {
            printf("Exiting communication...\n");
            break;
        }
    }

    // Close the socket
    close(sock);

    return 0;
}
