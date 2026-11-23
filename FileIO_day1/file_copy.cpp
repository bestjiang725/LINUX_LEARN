
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cerrno>
#include <cstring>

using namespace std;

int main(){
    int fd_in=open("source.txt",
    O_RDONLY,
    0644
    );
    if(fd_in==-1){
        perror("open source");
        return 1;
    }
    int fd=open("target.txt",

    O_WRONLY | O_CREAT | O_TRUNC,
    0644
    );
    if(fd==-1){
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