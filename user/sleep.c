#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "../user/user.h"

int main(int argc, char* argv[]) {
    if (argc < 2) {
        fprintf(2, "usage: sleep...\n");
        exit(1);
    }
    uint sleep_num = atoi(argv[1]);

    sleep(sleep_num);
    exit(0);
}