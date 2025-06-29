#ifndef ALL_HPP
#define ALL_HPP

#include <cstring>
#include <vector>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <poll.h>
#include <sstream>
#include <csignal>
#include <iostream>
#include "commands.hpp"

#define RED "\e[1;31m"
#define WHI "\e[0;37m"
#define GRE "\e[1;32m"
#define YEL "\e[1;33m"

class Client
{
private:
	int Fd;
	std::string IPadd;
	int isAut;
public:
	Client(){this->isAut=0;};
	int GetFd(){return Fd;}
	int getAut(void);
	void setAut(int value){this->isAut = value;}
	void SetFd(int fd){Fd = fd;}
	void setIpAdd(std::string ipadd){IPadd = ipadd;}
	bool IsAuthenticated() const;
	void SetAuthenticated(bool status);
};









class Server
{
private:
	int Port;
	std::string pass;
	int SerSocketFd;
	static bool Signal;
	std::vector<Client> clients;
	std::vector<struct pollfd> fds;
public:
	Server(){SerSocketFd = -1;}
	void ServerInit(int port,std::string pass);
	void SerSocket();
	void AcceptNewClient();
	void ReceiveNewData(int fd,Server *server);
	void authen();
	static void SignalHandler(int signum);
	int getClientaut(int fd) {
		for (size_t i = 0; i < clients.size(); i++) {
			if (clients[i].GetFd() == fd)
				return clients[i].getAut();
		}
		return -1;
	}
	std::string getpass(void) {
		return pass;
	}
	void setpass(std::string pass) {
		std::cout << "Server password set to: " << pass << std::endl;
		this->pass = pass;
	}
	void CloseFds();
	void ClearClients(int fd);
	/////////////////////////////////////////////////////
	void SendMessage(int fd, const std::string& message);
	void AuthenticateClient(int fd, const std::string& password);
	void SetClientAuthenticated(int fd, bool status);
	bool IsClientAuthenticated(int fd);
	
};

#endif