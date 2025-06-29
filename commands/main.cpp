#include "all.hpp"
#include <cstdlib>
#include "commands.hpp"


int Client::getAut(void) {
    return this->isAut;
}

bool Client::IsAuthenticated() const {
    return this->isAut == 1;
}

void Client::SetAuthenticated(bool status) {
    this->isAut = status ? 1 : 0;
}

void Server::ClearClients(int fd){
	for(size_t i = 0; i < fds.size(); i++){
		if (fds[i].fd == fd)
			{fds.erase(fds.begin() + i); break;}
	}
	for(size_t i = 0; i < clients.size(); i++){
		if (clients[i].GetFd() == fd)
			{clients.erase(clients.begin() + i); break;}
	}
}

bool Server::Signal = false;

void Server::SignalHandler(int signum)
{
	(void)signum;
	std::cout << std::endl << "Signal Received!" << std::endl;
	Server::Signal = true;
}

void Server::CloseFds(){
	for(size_t i = 0; i < clients.size(); i++){
		std::cout << RED << "Client <" << clients[i].GetFd() << "> Disconnected" << WHI << std::endl;
		close(clients[i].GetFd());
	}
	if (SerSocketFd != -1){
		std::cout << RED << "Server <" << SerSocketFd << "> Disconnected" << WHI << std::endl;
		close(SerSocketFd);
	}
}

void Server::SendMessage(int fd, const std::string& message) {
	std::string fullMessage = message + "\r\n";
	send(fd, fullMessage.c_str(), fullMessage.length(), 0);
}

void Server::AuthenticateClient(int fd, const std::string& password) {
	std::cout << password << std::endl;
	if (password == this->pass) {
		SetClientAuthenticated(fd, true);
		SendMessage(fd, ":server 001 * :Welcome to the IRC Server!");
		std::cout << GRE << "Client <" << fd << "> authenticated successfully" << WHI << std::endl;
	} else {
		SendMessage(fd, ":server 464 * :Password incorrect");
		std::cout << RED << "Client <" << fd << "> authentication failed" << WHI << std::endl;
	}
}

void Server::SetClientAuthenticated(int fd, bool status) {
	for (size_t i = 0; i < clients.size(); i++) {
		if (clients[i].GetFd() == fd) {
			clients[i].SetAuthenticated(status);
			break;
		}
	}
}

bool Server::IsClientAuthenticated(int fd) {
	for (size_t i = 0; i < clients.size(); i++) {
		if (clients[i].GetFd() == fd) {
			return clients[i].IsAuthenticated();
		}
	}
	return false;
}

// In ReceiveNewData
void Server::ReceiveNewData(int fd, Server *server) {
    char buff[1024];
    memset(buff, 0, sizeof(buff));

    ssize_t bytes = recv(fd, buff, sizeof(buff) - 1, 0);

    if (bytes <= 0) {
        if (bytes == 0) {
            std::cout << RED << "Client <" << fd << "> Disconnected" << WHI << std::endl;
        } else {
            std::cerr << RED << "Error receiving data from client <" << fd << ">" << WHI << std::endl;
        }
        ClearClients(fd);
        close(fd);
        return;
    }

    buff[bytes] = '\0';
    std::cout << YEL << "Client <" << fd << "> Data: " << WHI << buff;
    std::stringstream ss(buff);
    std::string line;
    while (std::getline(ss, line)) {
        // Remove \r if present
if (!line.empty() && *(line.end() - 1) == '\r') {
    line.erase(line.length() - 1);
}
        if (!line.empty()) {
            Acommands commands;
            commands.getCommand(fd, server, const_cast<char*>(line.c_str()));
        }
    }
}

void Server::AcceptNewClient()
{
	Client cli;
	struct sockaddr_in cliadd;
	struct pollfd NewPoll;
	socklen_t len = sizeof(cliadd);

	int incofd = accept(SerSocketFd, (sockaddr *)&(cliadd), &len);
	if (incofd == -1)
		{std::cout << "accept() failed" << std::endl; return;}

	if (fcntl(incofd, F_SETFL, O_NONBLOCK) == -1)
		{std::cout << "fcntl() failed" << std::endl; return;}

	NewPoll.fd = incofd;
	NewPoll.events = POLLIN;
	NewPoll.revents = 0;

	cli.SetFd(incofd);
	cli.setIpAdd(inet_ntoa((cliadd.sin_addr)));
	clients.push_back(cli);
	fds.push_back(NewPoll);
    
	std::cout << GRE << "Client <" << incofd << "> Connected" << WHI << std::endl;
}

void Server::SerSocket()
{
	int en = 1;
	struct sockaddr_in add;
	struct pollfd NewPoll;
	add.sin_family = AF_INET;
	add.sin_addr.s_addr = INADDR_ANY;
	add.sin_port = htons(this->Port);

	SerSocketFd = socket(AF_INET, SOCK_STREAM, 0);
	if(SerSocketFd == -1)
		throw(std::runtime_error("faild to create socket"));

	if(setsockopt(SerSocketFd, SOL_SOCKET, SO_REUSEADDR, &en, sizeof(en)) == -1)
		throw(std::runtime_error("faild to set option (SO_REUSEADDR) on socket"));
	 if (fcntl(SerSocketFd, F_SETFL, O_NONBLOCK) == -1)
		throw(std::runtime_error("faild to set option (O_NONBLOCK) on socket"));
	if (bind(SerSocketFd, (struct sockaddr *)&add, sizeof(add)) == -1)
		throw(std::runtime_error("faild to bind socket"));
	if (listen(SerSocketFd, SOMAXCONN) == -1)
		throw(std::runtime_error("listen() faild"));

	NewPoll.fd = SerSocketFd;
	NewPoll.events = POLLIN;
	NewPoll.revents = 0;
	fds.push_back(NewPoll);
}

void Server::ServerInit(int _port,std::string pass)
{
	this->Port = _port;
    this->setpass(pass);
	SerSocket();

	std::cout << GRE << "Server <" << SerSocketFd << "> Connected" << WHI << std::endl;
	std::cout << "Waiting to accept a connection...\n";

	while (Server::Signal == false){
		if((poll(&fds[0],fds.size(),-1) == -1) && Server::Signal == false)
			throw(std::runtime_error("poll() faild"));

		for (size_t i = 0; i < fds.size(); i++){
			if (fds[i].revents & POLLIN){
				if (fds[i].fd == SerSocketFd){
					AcceptNewClient();
                }else
					ReceiveNewData(fds[i].fd,this);
			}
		}
	}
	CloseFds();
}

int main(int ac,char **av)
{
	if (ac != 3) {
		std::cerr << RED << "Usage: " << av[0] << " <port> <password>" << WHI << std::endl;
		return 1;
	}

	Server ser;
	int port = atoi(av[1]);
	std::string pass = av[2];

	std::cout << "---- SERVER ----" << std::endl;
	try {
		signal(SIGINT, Server::SignalHandler);
		signal(SIGQUIT, Server::SignalHandler);
		ser.ServerInit(port, pass);
	} catch (const std::exception &e) {
		ser.CloseFds();
		std::cerr << e.what() << std::endl;
	}
	std::cout << "The Server Closed!" << std::endl;
}