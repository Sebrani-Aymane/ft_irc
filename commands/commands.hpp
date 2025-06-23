#ifndef COMMANDS_HPP
#define COMMANDS_HPP
#include <iostream>
#include <string>

class Server;

class Acommands {
private:
    std::string name;
    std::string args;
    
public:
    virtual ~Acommands() = default;
    void execute(const std::string& server_name, const std::string& client_name);
    std::string getName(void);
    void set_name(const std::string& name);
    std::string getArgs(void);
    std::string getFirstWord(char *buff);
    std::string getCommand( int fd, Server *server, char *command);
};

#endif