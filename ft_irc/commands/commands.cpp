#include "commands.hpp"

std::string Acommands::getFirstWord(char *buff){
    std::string input;
    for (int i=0;i <= 1025;i++)
    {
    if (!isalnum(buff[i]))
        input [i] = buff[i];
}
std::cout <<input<<std::endl;
}