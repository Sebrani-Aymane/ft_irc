#ifndef CLIENT_HPP
#define CLIENT_HPP
#include <iostream>
#include <string>
class Client
{
private:
	int Fd;
	std::string IPadd;
	int isAut;
	std::string Nickname;
	std::string Username;
	std::string Realname;
public:
	int ispassed;
	int isnicked;
	int isusered;
	Client();
	int GetFd() const ;
	int getAut(void);
	void setAut(int value);
	void SetFd(int fd);
	void setIpAdd(std::string ipadd);
	bool IsAuthenticated() const;
	void SetAuthenticated(bool status);
	void SetNickname(const std::string& nickname);
	std::string GetNickname() const;
	void SetUsername(const std::string& username)  ;
	std::string GetUsername() const;
	std::string GetRealname() const;
	void SetRealname(const std::string& realname)  ;
};

#endif