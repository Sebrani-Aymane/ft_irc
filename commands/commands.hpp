#ifndef COMMANDS_HPP
#define COMMANDS_HPP


#include <iostream>
#include  <string>
#include "Pass.hpp"

class Acommands{
    private : 
    std::string name;

    std::string args;
    public:

    void execute(std::string sever_name,std::string client_name);
    std::string getName(void);
    void set_name(std::string);
    std::string getArgs(void);
    std::string getFirstWord(char *buff);
    std::string getCommand(std::string line,int fd,Server *srver,char *command);
};

#endif