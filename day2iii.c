#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024  // Buffer size for reading and writing

int main(int argc, char *argv[]) {
	int source_fd, dest_fd, bytes_read, bytes_written;
	char buffer[BUFFER_SIZE];  // Buffer to hold data during copy

	// Step 1: Get the name of the source and destination file from the command line
	if (argc != 3) {
    	perror("Usage: ./copyfile <source_file> <destination_file>");
    	return 1;
	}

	// Step 2: Open the source file in read-only mode
	source_fd = open(argv[1], O_RDONLY);
	// Step 3: If the source file could not be opened, print an error message
	if (source_fd == -1) {
    	perror("Error opening source file");
    	return 1;
	}

	// Step 4: Create the destination file (open it in write-only mode, create it if it doesn't exist)
	dest_fd = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	// Step 5: If the destination file could not be opened, print an error message
	if (dest_fd == -1) {
    	perror("Error opening destination file");
    	close(source_fd);  // Close the source file before exiting
    	return 1;
	}

	// Step 6: Read contents from the source file and store them in the destination file
	while ((bytes_read = read(source_fd, buffer, BUFFER_SIZE)) > 0) {
    	bytes_written = write(dest_fd, buffer, bytes_read);
    	if (bytes_written != bytes_read) {
        	perror("Error writing to destination file");
        	close(source_fd);
        	close(dest_fd);
        	return 1;
    	}
	}

	// Check if there was an error while reading the source file
	if (bytes_read == -1) {
    	perror("Error reading source file");
	}

	// Close both the source and destination files
	close(source_fd);
	close(dest_fd);

	printf("File copied successfully from '%s' to '%s'\n", argv[1], argv[2]);

	return 0;  // Return success
}
