#ifndef DOCKER_HPP
#define DOCKER_HPP

#include <string>

class Docker
{
private:
    std::string cmd;
    std::string root_dir;
    void set_rootdir();

    bool proc;
public:
    Docker(std::string root_dir, std::string c);
    ~Docker();
    void start_cmd();
    void set_mount();
    void set_umount();
};

#endif