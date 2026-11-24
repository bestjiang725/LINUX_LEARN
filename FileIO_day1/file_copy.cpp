
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>

using namespace std;

int main(int argc,char *argv[]){
    if(argc!=3){
        std::cerr<<"用法："<<argv[0]<<endl;
        return 1;
    }
    int fd_in = open(argv[1], O_RDONLY);
if (fd_in == -1) {
    perror("open source");
    return 1;
}

int fd = open(argv[2], O_WRONLY | O_TRUNC | O_CREAT, 0644);
if (fd == -1) {
    perror("open target");
    close(fd_in);
    return 1;
}
    char buffer[4096];
    while(1){
        ssize_t n=read(fd_in,buffer,sizeof(buffer));
        if(n==-1){
            if(errno==EINTR){
                continue;
            }
            perror("read");
            close(fd_in);
            close(fd);
            return 1;
        }
        if(n==0)break;
        ssize_t tol=0;
        while(tol<n){
            ssize_t has=write(fd,
            buffer+tol,
            n-tol
            );
            if(has==-1){
                if (errno == EINTR) {
                continue;
            }

            perror("write");
            close(fd_in);
            close(fd);
            return 1;
            }
            if(has==0){
                std::cerr<<"write 0"<<endl;
                return 1;
            }
            tol+=has;

        }


    }
    close(fd_in);
    close(fd);

    cout<<"finished"<<endl;
    return 0;



}