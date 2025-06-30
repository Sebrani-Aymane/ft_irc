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
    void execute(const std::string& server_name, const std::string& client_name);
    std::string getName(void);
    void set_name(const std::string& name);
    std::string getArgs(void);
    std::string getFirstWord(const char *buff)const ;
    std::string getCommand( int fd, Server *server,const  char *command) const  ;
    std::string getParam(std::string line)const ;
    void handleNick(int fd, Server *server, const std::string& nickname)const ;
    void handleUser(int fd, Server *server, const std::string& command)const ;
    bool parseNickname(const std::string& nickname)const ;
    bool parseUsename(const std::string& username)const ;
    std::string getLastWord(const std::string& line) const ;
};

#endif