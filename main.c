#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#include <string.h>

#define OUTFILE			"out.txt"
#define GRIDPATH		"/home/blacksocks/Documents/Programming/MotMeleeMaker/grid/main"
#define GRIDPRGM		"main"

static char *argvChild[] = {GRIDPRGM, 0, OUTFILE, NULL};

int main(int argc, char * argv[])
{
	if(argc < 2 || argc > 2)
	{
		printf("Usage: main filein\n"
		"  filein: (string) input text file with one word per line\n");
		return 1;
	}

	// create grid using another program
	pid_t pid = fork();
	if(pid == EAGAIN || pid == ENOMEM || pid == ENOSYS)
	{
		printf("[ERROR] An error occured during fork\n");
		return 1;
	}
    if(pid == 0)
	{
		// child process
		argvChild[1] = argv[1];
        execv(GRIDPATH, argvChild);
        printf("[ERROR] An error occured during execv: %s\n", strerror(errno));
		return 1;
    }
    else
	{
		// pid != 0, parent process
		// wait for child to exit
		int status;
		if(waitpid(pid, &status, 0) == -1)
		{
			printf("[ERROR] An error occured dunring waitpid\n");
			return 1;
		}
        if(status)
		{
			printf("[ERROR] Child returned: %d\n", status);
			return 1;
		}
    }

	
	printf("[INFO] Program ended successfully\n");
	return 0;
}
