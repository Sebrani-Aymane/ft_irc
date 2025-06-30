#include "Pass.hpp"
#include "all.hpp"

int Pass::authenticateClient(std::string input, Server &server, int fd) {
    if (server.IsClientAuthenticated(fd)) {
        server.SendMessage(fd, ":server 462 * :You may not reregister");
        return -1;
    }
    std::string password;
    size_t spacePos = input.find(' ');
    if (spacePos != std::string::npos) {
        password = input.substr(spacePos + 1);
        while (!password.empty()) {
            char lastChar = password[password.length() - 1];
            if (lastChar == ' ' || lastChar == '\n' || lastChar == '\r') {
                password.erase(password.length() - 1);
            } else {
                break;
            }
        }
    }

    // Check if password was provided
    if (password.empty()) {
        server.SendMessage(fd, ":server 461 PASS :Not enough parameters");
        return -1;
    }

    // Authenticate
    server.AuthenticateClient(fd, password);
    return server.IsClientAuthenticated(fd);
}