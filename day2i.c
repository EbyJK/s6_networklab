#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <limits.h>

int main() {
	pid_t pid;
    
	// Step 1: Create a new process using fork()
	pid = fork();
    
	if (pid < 0) {
    	// Step 2: If the process is not created, report an error and terminate
    	perror("Fork failed");
    	exit(1);
	}
    
	if (pid == 0) {
    	// Step 3: Child Process
    	printf("Child Process: PID = %d\n", getpid());
   	 
    	// Step 4: Display the present working directory in the child process
    	char cwd[PATH_MAX];
    	if (getcwd(cwd, sizeof(cwd)) != NULL) {
        	printf("Child Process Working Directory: %s\n", cwd);
    	} else {
        	perror("getcwd() failed in child");
        	exit(1);
    	}
   	 
    	// Step 5: Print status (Child process) - In real scenarios, you would use wait() in parent
    	printf("Child Process Status: Executing...\n");

    	exit(0);  // Exit child process
	} else {
    	// Step 3: Parent Process
    	printf("Parent Process: PID = %d, Child PID = %d\n", getpid(), pid);
   	 
    	// Step 4: Display the present working directory in the parent process
    	char cwd[PATH_MAX];
    	if (getcwd(cwd, sizeof(cwd)) != NULL) {
        	printf("Parent Process Working Directory: %s\n", cwd);
    	} else {
        	perror("getcwd() failed in parent");
        	exit(1);
    	}
   	 
    	// Step 5: Parent waits for child process to finish
    	wait(NULL);  // Parent waits for the child to terminate
   	 
    	printf("Parent Process Status: Child has finished execution.\n");
	}

	return 0;
}
