#include <iostream>
#include <string>
#include <csignal>
#include <sys/wait.h>

#include "Docker.hpp"

#define STACK_SIZE (1024 * 1024)
char child_stack[STACK_SIZE];

std::string cmd = "/bin/sh";
std::string root_dir = "/home/luluteam/gyj/myRoot";

static void die(const char *error_msg)
{
    perror(error_msg);
    exit(1);
}

int entrance(void *container)
{
    Docker *docker = static_cast<Docker *>(container);
    docker->start_cmd();
    return 0;
}

int main(int argc, char* argv[])
{
    Docker d(root_dir, cmd);
    pid_t child_pid = clone(entrance,
                            child_stack + STACK_SIZE,
                            SIGCHLD | CLONE_NEWUTS | CLONE_NEWNS | CLONE_NEWPID | CLONE_NEWNET,
                            &d);
    if (child_pid < 0)
    {
        perror("clone child failed.");
    }
    waitpid(child_pid, NULL, 0);
    return 0;
}