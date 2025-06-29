#ifndef PASS_HPP
#define PASS_HPP

#include "all.hpp"
#include <string>

class Pass {
public:
    static int checkPass(std::string input, Server &server, int fd);
    static int authenticateClient(std::string input, Server &server, int fd);
};

#endif