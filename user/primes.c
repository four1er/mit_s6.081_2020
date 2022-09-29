#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "../user/user.h"

void child_process(int pp_read) {
    int i;
    int pp2[2];
    pipe(pp2);
    int ret = read(pp_read, &i, 1);
    if (!ret) {
        close(pp_read);
        printf("close pid: %d\n",getpid());
        exit(0);
    }
    if (fork() == 0) {
        close(pp2[1]);
        child_process(pp2[0]);
        
    } else {
        // filter numbers
        close(pp2[0]);
        int res = i;
        printf("prime %d\n", res);
        while (read(pp_read, &i, 1)) {
            if (i % res != 0) {
                write(pp2[1], &i, 1);
            }
        }
        close(pp2[1]);
        wait(0);
        close(pp_read);
        printf("close pid: %d\n",getpid());
        exit(0);
    }
}

int main() {
    int pp1[2];
    pipe(pp1);
    if (fork() == 0) {
        // child process
        close(pp1[1]);
        child_process(pp1[0]);
        exit(0);
    } else {
        // parent process
        close(pp1[0]);
        for (int i = 2; i <= 35; i++) {
            if (i == 2) {
                printf("prime %d\n", i);
            }
            if (i % 2 != 0) {
                write(pp1[1], &i, 1);
            }
        }
        close(pp1[1]);
        wait(0);
        exit(0);
    }
    exit(0);
}