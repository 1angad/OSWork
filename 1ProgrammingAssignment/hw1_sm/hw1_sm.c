#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char *argv[])
{
pid_t pid, pid1;
int n;
	

	if (argc == 1) {
		fprintf(stderr,"Usage: ./a.out <starting value>\n");

		return -1;
	}

	n = atoi(argv[1]);

	/* add your code below, following the code structure of Figure 3.34 (page 152) */
	int shm_fd;
	void *ptr;
	const char *name = "OS";
	shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
	ftruncate(shm_fd, 4096);
	ptr = mmap(0, 4096, PROT_WRITE, MAP_SHARED, shm_fd, 0);
	/* fork a child process*/
	pid = fork();
	
	if(pid < 0) { /* error occurred */
		fprintf(stderr, "Fork Failed");
		return 1;
	} else if (pid == 0) { /*child process */ 
		pid1 = getpid();
		printf("child: pid = %d\n", pid); /* A */
		printf("child: pid1 = %d\n", pid1); /* B */
		sprintf(ptr, "%d, ", n);
		ptr += strlen(ptr);
		while(n > 1) {
			if(n % 2 == 0) {
				n /= 2;
			} else {
				n = 3 * n + 1;
			}
			sprintf(ptr,"%d, ", n);
			ptr += strlen(ptr);
		}
		
	} else { /* parent process */
		pid1 = getpid();
		printf("parent: pid = %d\n", pid); /* C */
		printf("parent: pid1 = %d\n", pid1); /* D */
		wait(NULL);
		printf("pid = %d ", pid1);
		printf("Sequence: %s \n", (char *)ptr);		
	}
	shm_unlink(name);
	return 0;
}
