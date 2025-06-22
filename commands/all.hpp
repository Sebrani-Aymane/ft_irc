
#ifndef ALL_HPP
#define ALL_HPP
#include <cstring>
#include <vector> //-> for vector
#include <sys/socket.h> //-> for socket()
#include <sys/types.h> //-> for socket()
#include <netinet/in.h> //-> for sockaddr_in
#include <fcntl.h> //-> for fcntl()
#include <unistd.h> //-> for close()
#include <arpa/inet.h> //-> for inet_ntoa()
#include <poll.h> //-> for poll()
#include <csignal> //-> for signal()
#include <iostream>
#include "commands.hpp"
//-------------------------------------------------------//
#define RED "\e[1;31m" //-> for red color
#define WHI "\e[0;37m" //-> for white color
#define GRE "\e[1;32m" //-> for green color
#define YEL "\e[1;33m" //-> for yellow color
//-------------------------------------------------------//
class Acommands;
class Client //-> class for client
{
private:
	int Fd; //-> client file descriptor
	std::string IPadd; //-> client ip address
	int isAut;
public:
	Client(){this->isAut=0;}; //-> default constructor
	int GetFd(){return Fd;} //-> getter for fd
	int getAut(void);
	void setAut(int value);
	void SetFd(int fd){Fd = fd;} //-> setter for fd
	void setIpAdd(std::string ipadd){IPadd = ipadd;} //-> setter for ipadd
};

class Server //-> class for server
{
private:
	int Port; //-> server port
    std::string pass;

	int SerSocketFd; //-> server socket file descriptor
	static bool Signal; //-> static boolean for signal
	std::vector<Client> clients; //-> vector of clients
	std::vector<struct pollfd> fds; //-> vector of pollfd
public:
	Server(){SerSocketFd = -1;} //-> default constructor

	void ServerInit(int port,std::string pass); //-> server initialization
	void SerSocket(); //-> server socket creation
	void AcceptNewClient(); //-> accept new client
	void ReceiveNewData(int fd); //-> receive new data from a registered client
	void authen();
	static void SignalHandler(int signum); //-> signal handler
	int getClientaut(int fd){
		for (int i=0; i<=50000;i++)
		{
			if (clients[i].GetFd() ==fd)
				 return(clients[i].getAut());
		}
			
	};
	
	void CloseFds(); //-> close file descriptors
	void ClearClients(int fd); //-> clear clients
};
#endif