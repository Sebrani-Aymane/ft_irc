#include "commands.hpp"
#include "all.hpp"

std::string Acommands::getFirstWord(char *buff)
{
    std::string input;
    input = std::string(buff);
    std::string firstWord;
    int i = 0;
    while (i < 4 && buff[i] != '\0' && buff[i] != ' ') {
        firstWord += buff[i];
        i++;
    }
    std::cout << firstWord << std::endl;
    return(firstWord);
}

std::string Acommands::getCommand(std::string line,int fd,Server *server,char *command)
{
    Pass pass;
    if (line == "PASS" && !(*server).getClientaut(fd))
    {
        pass.checkPass(command);
    }

}