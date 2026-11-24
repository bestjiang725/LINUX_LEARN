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

    pid_t pid = fork();

    if (pid == -1) {
        std::perror("fork");
        return 1;
    }

    if (pid == 0) {
        val= 20;
    if (pid == 0) {
    std::printf("child: pid=%ld, parent=%ld\n",
                static_cast<long>(getpid()),
                static_cast<long>(getppid()));

    return 7;  // 实验用：让孩子返回一个容易辨认的值
}
    } else {
    std::printf("parent: waiting for child=%ld\n",
                static_cast<long>(pid));

    int status;
    pid_t result;

    do {
        result = waitpid(pid, &status, 0);
    } while (result == -1 && errno == EINTR);

    if (result == -1) {
        std::perror("waitpid");
        return 1;
    }
    if (WIFEXITED(status)) {
    std::printf("parent: child exit code=%d\n",
                WEXITSTATUS(status));
} else if (WIFSIGNALED(status)) {
    std::printf("parent: child killed by signal=%d\n",
                WTERMSIG(status));
}

    std::printf("parent: child has ended\n");
}

    return 0;
}