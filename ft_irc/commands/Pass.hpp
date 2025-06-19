#ifndef PASS_HPP

#define PASS_HPP


#include "commands.hpp"

#include "all.hpp"

class Pass : public  Acommands{
    private:

    int client_id;
    int client_sokt;
    public :

    std::string getId(std::string name_port);
    void execute(Server server_name,Client client_name)
    void

};


#endif