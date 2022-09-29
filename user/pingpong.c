#include "../kernel/types.h"
#include "../kernel/stat.h"
#include "../user/user.h"

int main(){
    int p2s[2];
    int s2p[2];
    pipe(p2s);
    pipe(s2p);
    if(fork()==0){
        // child process;
        // close p2s 1
        // close s2p 0
        char read_buf[5]={};
        char send_buf[5]="pong";
        close(p2s[1]);
        close(s2p[0]);
        read(p2s[0],read_buf,sizeof(read_buf));
        printf("%d: received %s\n",getpid(),read_buf);
        write(s2p[1],send_buf,sizeof(send_buf));
        close(p2s[1]);
        close(s2p[0]);
        exit(0);
    }else{
        // parent process;
        // close p2s[0]
        // close s2p[1];
        char send_buf[5]="ping";
        char read_buf[5]={};
        close(p2s[0]);
        close(s2p[1]);
        write(p2s[1], send_buf, sizeof send_buf);
        wait(0);
        read(s2p[0],read_buf,sizeof(read_buf));
        printf("%d: received %s\n",getpid(),read_buf);
        close(s2p[1]);
        close(p2s[0]);
        exit(0);
    }

}