#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "../kernel/param.h"
#include "../user/user.h"

#define MAXLINE 1024

int main(int argc, char* argv[]) {
    char* cmd = argv[1];
    char* params[MAXARG];
    int args_index = 0;
    char line[MAXLINE];
    int n;

    for (int i = 1; i < argc; i++) {
        params[args_index++] = argv[i];
    }

    while ((n = read(0, line, MAXLINE)) > 0) {
        if (fork() == 0) {
            char* arg = (char*)malloc(sizeof(line));
            int index = 0;
            for (int i = 0; i < n; i++) {
                if (line[i] == ' ' || line[i] == '\n') {
                    arg[index] = 0;
                    params[args_index++] = arg;
                    index = 0;
                    arg = (char*)malloc(sizeof(line));
                } else {
                    arg[index++] = line[i];
                }
            }
            arg[index] = 0;
            params[args_index] = 0;
            exec(cmd, params);
        } else {
            wait(0);
        }
    }
    exit(0);
}