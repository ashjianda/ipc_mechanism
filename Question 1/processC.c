#include "header.h"

#define SHMSZ 1024
int main() {
    int shmid_int, shmid_str, shmid_pid;
    key_t key_int, key_str, key_pid;
    int *int_mem, *pid_mem;
    char *str_mem;

    // Generate a unique key for the integer shared memory
    key_int = ftok("/tmp", 'I');
    if (key_int == -1) {
        perror("ftok for integer");
        exit(1);
    }

    // Generate a unique key for the string shared memory
    key_str = ftok("/tmp", 'S');
    if (key_str == -1) {
        perror("ftok for string");
        exit(1);
    }

    // Generate a unique key for the pid shared memory
    key_pid = ftok("/tmp", 'P');
    if (key_pid == -1) {
        perror("ftok for pid");
        exit(1);
    }

    // Create shared memory for the integer
    shmid_int = shmget(key_int, sizeof(int), 0666);
    if (shmid_int < 0) {
        perror("shmget for integer");
        exit(1);
    }

    // Create shared memory for the string
    shmid_str = shmget(key_str, SHMSZ, 0666);
    if (shmid_str < 0) {
        perror("shmget for string");
        exit(1);
    }

    // Create shared memory for the pid
    shmid_pid = shmget(key_pid, sizeof(getpid()), IPC_CREAT | 0666);
    if (shmid_pid < 0) {
        perror("shmget for pid");
        exit(1);
    }

    // Attach to the integer shared memory
    int_mem = (int *)shmat(shmid_int, NULL, 0);
    if (int_mem == (int *)-1) {
        perror("shmat for integer");
        exit(1);
    }

    // Attach to the string shared memory
    str_mem = (char *)shmat(shmid_str, NULL, 0);
    if (str_mem == (char *)-1) {
        perror("shmat for string");
        exit(1);
    }

    // Attach to the pid shared memory
    pid_mem = (int *)shmat(shmid_pid, NULL, 0);
    if (pid_mem == (int *)-1) {
        perror("shmat for pid");
        exit(1);
    }

    while(*int_mem != 20){
        sleep(1);
    }

    *int_mem = 30;
    *pid_mem = getpid();
    strcpy(str_mem, "I am Process C");
    sprintf(str_mem, "I am Process C");

    // Detach from shared memory
    shmdt(int_mem);
    shmdt(str_mem);
    shmdt(pid_mem);

    return 0;
}