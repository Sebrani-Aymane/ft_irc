#ifndef COMMANDS_HPP
#define COMMANDS_HPP

#include "all.hpp"
#include <iostream>
#include  <string>
class Acommands{
    private : 
    std::string name;
    Client  clients[100];
    std::string args;
    public:
    void execute(std::string sever_name,std::string client_name);
    std::string getName(void);
    void set_name(std::string);
    std::string getArgs(void);
    std::string getFirstWord(char *buff);
};

#endif