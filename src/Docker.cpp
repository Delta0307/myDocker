#include "Docker.hpp"
#include <iostream>
#include <unistd.h>
#include <sys/mount.h>

Docker::Docker(std::string r, std::string c) : root_dir(r), cmd(c), proc(0)
{
    set_rootdir();
}

Docker::~Docker()
{
    set_umount();
}

void Docker::set_mount()
{
    if (mount("none", "proc", "proc", 0, nullptr) < 0)
    {
        std::cout << "fail to mount proc!" << std::endl;
    }
    else
    {
        proc = true;
        std::cout << "mount success!" << std::endl;
    }
}

void Docker::set_umount()
{
    if (umount("/proc") < 0)
    {
        std::cout << "fail to umount proc!" << std::endl;
    }
    else
    {
        proc = false;
        std::cout << "umount success!" << std::endl;
    }
}

void Docker::start_cmd()
{
    set_mount();
    char *const child_args[] = {const_cast<char *>(cmd.c_str()), NULL};
    if (execv(cmd.c_str(), child_args) < 0)
    {
        std::cout << "fail to execute the command: " << cmd << std::endl;
    }
}

void Docker::set_rootdir()
{
    chdir(root_dir.c_str());
    chroot("./");
}