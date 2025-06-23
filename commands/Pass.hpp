#ifndef PASS_HPP

#define PASS_HPP

#include "all.hpp"

class Pass : public Acommands
{
    private:

    int client_id;
    int client_sokt;
    public :
    int checkPass(std::string input, Server &server);
    std::string getId(std::string name_port);
   // void execute(Server server_name,Client client_name);


};


#endif