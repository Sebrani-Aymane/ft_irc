#include "all.hpp"

#include "Pass.hpp"
std::string Acommands::getFirstWord(const char *buff) const {
    std::string line(buff);
    std::string word;
    for(size_t i=0; i < line.length(); i++) {
        if (line[i] == ' ' || line[i] == '\n' || line[i] == '\r') {
            break;
        }
        word += line[i];
    }
    if (word.empty()) {
        return "";
    }
    return word;
}

std::string Acommands::getParam(std::string line) const {
    std::string param;
    for (size_t i=0;i<line.length();i++) {
        while (line[i] == ' ' || line[i] == '\n' || line[i] == '\r') {
            i++;
        }
        if (i >= line.length()) {
            std::cout << "Error: No parameters found in the input." << std::endl;
            return "";
        }
        while (line[i] != ' ' && line[i] != '\n' && line[i] != '\r' && i < line.length()) {
            param += line[i];
            i++;
    }
}
return param;
}




bool Acommands::parseNickname(const std::string& nickname) const {
    if (!isalnum(nickname[0]) && nickname[0] != '-' && nickname[0] != '_') {
        return 0;
    }
    for (size_t i = 1; i < nickname.length(); i++) {
        if (!isalnum(nickname[i]) && nickname[i] != '-' && nickname[i] != '_' && nickname[i] != '[' && nickname[i] != ']' && nickname[i] != '\\') {
            return 0;
        }
    }
    return 1;
}







void Acommands::handleNick(int fd, Server *server, const std::string& nickname)const  {
    if (nickname.empty()) {
        server->SendMessage(fd, ":server 431 * :No nickname given");
        return;
    }
if (!parseNickname(nickname)) {
    server->SendMessage(fd, ":server 432 * " + nickname + " :Errone: Invalid nickname");
    return;
    std::vector<Client> clients = server->getClients();

 for (size_t i = 0; i < clients.size(); i++) {
    if (clients[i].GetFd() != fd && clients[i].GetNickname() == nickname) {
        server->SendMessage(fd, ":server 433 " + nickname + " :Nickname is already in use");
        return;
    }
}
    for (size_t i = 0; i < clients.size(); i++) {
        if (clients[i].GetFd() == fd) {
            clients[i].SetNickname(nickname);
            server->SendMessage(fd, ":server 001 " + nickname + " :Welcome to the server!");
        }
    }
}
}





bool Acommands::parseUsename(const std::string& username) const {
    if (username.empty() || username.length() > 16) {
        return false;
    }
    for (size_t i = 0; i < username.length(); i++) {
        if (!isalnum(username[i]) && username[i] != '-' && username[i] != '_' && username[i] != '.' && username[i] != '@') {
            return false;
        }
    }
    
    return true;
}







std::string Acommands::getLastWord(const std::string& line) const {
    size_t lastSpace = line.find_last_of(' ');
    if (lastSpace == std::string::npos) {
        return line;
    }
    return line.substr(lastSpace + 1);
}






void Acommands::handleUser(int fd, Server *server, const std::string& command) const {
    std::string username;
    username = getParam(command);
    if (username.empty()) {
        server->SendMessage(fd, ":server 461 USER :Not enough parameters");
        return;
    }
    if (!parseUsename(username)) {
        server->SendMessage(fd, ":server 432 * " + username + " :Errone: Invalid username");
        return;
    }
     std::vector<Client> clients = server->getClients();
     for (size_t i = 0; i < clients.size(); i++) {
    if (clients[i].GetFd() != fd && clients[i].GetUsername() == username) {
        server->SendMessage(fd, ":server 433 " + username + " :usernanme is already in use");
        return;
    }
}
    for (size_t i = 0; i < clients.size(); i++) {
        if (clients[i].GetFd() == fd) {
            clients[i].SetUsername(username);
            clients[i].SetRealname(getLastWord(command));
            server->SendMessage(fd, ":server 001 " + username + " :Welcome to the server!");
            return;
        }
    }
}


std::string Acommands::getCommand (int fd, Server *server,const  char *command) const {
    std::string cmd = getFirstWord(command);
    if (cmd.empty()) {
        std::cout << "Error: No command found in the input." << std::endl;
        return "bad";
    }
    if (!server->IsClientAuthenticated(fd) && cmd != "PASS") {
        server->SendMessage(fd, ":server 451 * :You have not registered");
        return "bad";
    }
    if (cmd == "PASS") {
        Pass pass;
        if (pass.authenticateClient(command, *server, fd) == -1) {
            close (fd);
            return "bad";
        }
    }
    else if (cmd == "NICK") {
        std::string nickname = getParam(command);
        handleNick(fd, server, nickname);
    }
    else if (cmd == "USER") {
    handleUser(fd,server,command);
    }
    else {
        if (server->IsClientAuthenticated(fd)) {
            server->SendMessage(fd, ":server 421 " + cmd + " :Unknown command");
        } else {
            server->SendMessage(fd, ":server 451 * :You have not registered");
        }
        std::cout << "Error: Unknown command '" << cmd << "'." << std::endl;
    }
    return "good";
}