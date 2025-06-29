#include "commands.hpp"
#include "Pass.hpp"
std::string Acommands::getFirstWord(char *buff) {
    std::string line(buff);
    std::string word;
    for(size_t i=0; i < line.length(); i++) {
        if (line[i] == ' ' || line[i] == '\n' || line[i] == '\r') {
            break;
        }
        word += line[i];
    }
    if (word.empty()) {
        std::cout << "Error: No command found in the input." << std::endl;
        return "";
    }
    return word;
}


std::string Acommands::getCommand(int fd, Server *server, char *command) {
    std::string cmd = getFirstWord(command);
    if (cmd.empty()) {
        std::cout << "Error: No command found in the input." << std::endl;
        return "";
    }
    if (!server->IsClientAuthenticated(fd) && cmd != "PASS") {
        server->SendMessage(fd, ":server 451 * :You have not registered");
        return "";
    }
    if (cmd == "PASS") {
        Pass pass;
        if (pass.authenticateClient(command, *server, fd) == -1) {
            std::cout << "Authentication failed for client " << fd << std::endl;
        }
    }
    else if (cmd == "NICK") {
        // NICK command implementation
    }
    else if (cmd == "USER") {
        // USER command implementation
    }
    else {
        if (server->IsClientAuthenticated(fd)) {
            server->SendMessage(fd, ":server 421 " + cmd + " :Unknown command");
        } else {
            server->SendMessage(fd, ":server 451 * :You have not registered");
        }
        std::cout << "Error: Unknown command '" << cmd << "'." << std::endl;
    }
    return cmd;
}