#include<cstdio>
#include<sys/types.h>
#include<unistd.h>
#include<sys/wait.h>
#include<cerrno>

int main(){
     int val=10;
      std::printf("before fork: pid=%ld\n",
                static_cast<long>(getpid()));
    std::fflush(stdout);

    pid_t first=fork();

    if (first== -1) {
        std::perror(" first fork");
        return 1;
    }

    if (first== 0) {
        val= 20;
    std::printf("child: pid=%ld, parent=%ld\n",
                static_cast<long>(getpid()),
                static_cast<long>(getppid()));

    return 3; 
}

pid_t second=fork();

    if (second== -1) {
        std::perror("second fork");
        return 1;
    }

    if (second== 0) {
    std::printf("child: pid=%ld, parent=%ld\n",
                static_cast<long>(getpid()),
                static_cast<long>(getppid()));

    return 5; 
}


    std::printf("parent: waiting for first child=%ld\n",
                static_cast<long>(first));

    int status;
    pid_t result;

    {do {
        result = waitpid(first, &status, 0);
    } while (result == -1 && errno == EINTR);

    if (result == -1) {
        std::perror("waitpid");
        return 1;
    }
    if (WIFEXITED(status)) {
    std::printf("parent: first child exit code=%d\n",
                WEXITSTATUS(status));
} else if (WIFSIGNALED(status)) {
    std::printf("parent: first child killed by signal=%d\n",
                WTERMSIG(status));
}

    std::printf("parent: first child has ended\n");}
    
    {std::printf("parent: waiting for second child=%ld\n",
                static_cast<long>(second));


    do {
        result = waitpid(second, &status, 0);
    } while (result == -1 && errno == EINTR);

    if (result == -1) {
        std::perror("waitpid");
        return 1;
    }
    if (WIFEXITED(status)) {
    std::printf("parent:  second child exit code=%d\n",
                WEXITSTATUS(status));
} else if (WIFSIGNALED(status)) {
    std::printf("parent: second child killed by signal=%d\n",
                WTERMSIG(status));
}

    std::printf("parent: second child has ended\n");
}




    return 0;
}