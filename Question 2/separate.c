#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pid1 = fork();
    int pid2 = fork();

    if(pid1 == 0 && pid2 > 0){
        sleep(1);
        printf("20 I AM PROCESS B whose id is : %d\n", getpid());
    } else if(pid2 == 0 && pid1 > 0){
        sleep(2);
        printf("30 I AM PROCESS C whose id is : %d\n", getpid());
    } else if (pid1 > 0 && pid2 > 0){
        printf("10 I AM PROCESS A whose id is : %d\n", getpid());
        wait(NULL);
        wait(NULL);
        printf("Good Bye World, I am Done!!\n");
    } else {
        exit(0);
    }

    return 0;
}