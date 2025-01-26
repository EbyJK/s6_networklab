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
    socklen_t addr_len = sizeof(server_addr);

    // Create UDP socket
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) == -1) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    if (inet_pton(AF_INET, SERVER_IP, &server_addr.sin_addr) <= 0) {
        perror("Invalid address or Address not supported");
        exit(EXIT_FAILURE);
    }

    printf("Connected to the server (UDP, connectionless)\n");

    // Communication loop
    while (1) {
        // Ask the user for a message to send to the server
        printf("Enter message to send to server (type 'exit' to quit): ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;  // Remove newline character

        // Send message to server
        sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, addr_len);
        printf("Message sent to server\n");

        // Exit loop if the user types "exit"
        if (strcmp(buffer, "exit") == 0) {
            printf("Exiting communication...\n");
            break;
        }

        // Receive message from server
        memset(buffer, 0, sizeof(buffer));  // Clear the buffer
        int valread = recvfrom(sock, buffer, sizeof(buffer), 0, (struct sockaddr *)&server_addr, &addr_len);
        if (valread <= 0) {
            printf("Server disconnected or error occurred.\n");
            break;
        }
        printf("Message from server: %s\n", buffer);
    }

    // Close the socket
    close(sock);

    return 0;
}
