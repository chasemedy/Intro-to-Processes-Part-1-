#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>

void ChildProcess(void);

int main(void)
{
    pid_t pid1, pid2;
    int   status;
    int   i;

    pid1 = fork();
    if (pid1 == 0)
        ChildProcess();          /* first child runs, then exits inside here */

    pid2 = fork();
    if (pid2 == 0)
        ChildProcess();          /* second child runs, then exits inside here */

    /* Only the parent reaches this point */
    for (i = 0; i < 2; i++) {
        pid_t finished = wait(&status);
        printf("Child Pid: %d has completed\n", finished);
    }

    return 0;
}

void ChildProcess(void)
{
    int iterations, i;

    /* Seed here, per child, so the two children don't produce identical runs */
    srandom(time(NULL) ^ getpid());

    iterations = (random() % 30) + 1;      /* 1 to 30 */

    for (i = 0; i < iterations; i++) {
        printf("Child Pid: %d is going to sleep!\n", getpid());
        sleep((random() % 10) + 1);        /* 1 to 10 seconds */
        printf("Child Pid: %d is awake!\nWhere is my Parent: %d?\n",
               getpid(), getppid());
    }

    exit(0);
}