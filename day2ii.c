#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>  // For opendir(), readdir(), closedir()
#include <string.h>  // For strerror()
#include <errno.h>   // For errno

int main() {
	DIR *dir;
	struct dirent *entry;
	char *directory = "."; // Current directory

	// Open the directory stream
	dir = opendir(directory);
	if (dir == NULL) {
    	// If opendir fails, print error message
    	perror("opendir");
    	return 1;
	}

	printf("Contents of directory '%s':\n", directory);
    
	// Read entries in the directory
	while ((entry = readdir(dir)) != NULL) {
    	// Print the name of each entry in the directory
    	printf("%s\n", entry->d_name);
	}

	// Close the directory stream
	if (closedir(dir) == -1) {
    	// If closedir fails, print error message
    	perror("closedir");
    	return 1;
	}

	printf("Directory closed successfully.\n");
	return 0;
}

