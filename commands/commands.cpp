#include "commands.hpp"
#include "Pass.hpp"
std::string Acommands::getFirstWord(char *buff) {
    std::string line(buff);
    std::string word;
    for(int i=0; i < line.size(); i++) {
        if (line[i] == ' ' || line[i] == '\n' || line[i] == '\r') {
            break;
        }
        word += line[i];
    }
    if (word.empty()) {
        std::cerr << "Error: No command found in the input." << std::endl;
        return "";
    }
    return word;
}

std::string Acommands::getCommand(int fd, Server *server, char *command) {
    std::string cmd = getFirstWord(command);
    if (cmd.empty()) {
        std::cerr << "Error: No command found in the input." << std::endl;
        return "";
    }
    if (cmd == "PASS") {
        Pass pass;
        pass.checkPass(command,*server);
    }
    else if (cmd == "NICK")
    {
        Join join;
        join.set_name(command);
    }
    else {
        std::cerr << "Error: Unknown command '" << cmd << "'." << std::endl;
    }
    return cmd;
}