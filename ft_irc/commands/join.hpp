#ifndef JOIN_HPP

#define JOIN_HPP

#include "commands.hpp"


class Join : public  Acommands{
    private : 
    std::string commandName;
    std::string commandArgs;
    int numericReply;
  class NOCHANNELWITHTHATNAME : public std::exception
       {
        public:
           virtual const char *what() const throw();
        };
        
};

#endif