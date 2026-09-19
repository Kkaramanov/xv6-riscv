#include "kernel/types.h"
#include "user/user.h"
#include "kernel/stat.h"

void
run_child()
{
    pause(50);
    exit(1);
}

int
main(int argc, char *argv[])
{
    int mode = 0;
    if (argc > 1 && argv[1][0] == 'b') {
	mode = 1;
    }

    int parent_pid = getpid();
    int new_process = fork();

    if (new_process < 0) {
	fprintf(2, "Fork failed\n");
	exit(1);
    }
    
    if (new_process == 0) {
	run_child();
    } else {
	printf("PID parents %d\n PID chiled %d\n", parent_pid, new_process);
	if (mode == 1) {
	    printf("Kill chiled %d\n", new_process);
	    kill(new_process);
	}

	int status = 0;
	int close_pid = wait(&status);

	printf("Close PID %d\n exit code %d\n", close_pid, status);
	exit(0);
    }


}