#include "Pass.hpp"

int Pass::checkPass(std::string input, Server &server) {
   
 
    std::string pass = server.getpass(); 
    int client_fd = client.GetFd();

    std::string password;
    for (int i = 4; i < input.size(); i++) {
        if (input[i] == ' ' || input[i] == '\n' || input[i] == '\r') {
            continue;  
        }
        password += input[i]; 
    }
 std::cout <<"blass       " <<password << " blasss"<< std::endl;
    if(pass == password) {
        client.setAut(1);
        std::cout << "Client <" << client_fd << "authenticated." << std::endl;
        return 0;
    } else {
        std::cout << "Error: Incorrect password for client <" << client_fd  << std::endl;
        return -1;
    }
}