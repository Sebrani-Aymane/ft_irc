#include "all.hpp"


Client::Client() : Fd(-1), isAut(0) {}

int Client::getAut(void) {
    return this->isAut;
}
void Client::setAut(int value) {
    this->isAut = value;
}

bool Client::IsAuthenticated() const {
    return this->isAut == 1;
}

void Client::SetAuthenticated(bool status) {
    this->isAut = status ;
}
void Client::SetNickname(const std::string& nickname) {
    this->Nickname = nickname;
}
std::string Client::GetNickname() const {
    return this->Nickname;
}
void Client::SetUsername(const std::string& username) {
    this->Username = username;
}
std::string Client::GetUsername() const {
    return this->Username;
}
int Client::GetFd() const {
    return this->Fd;
}
void Client::SetFd(int fd) {
    this->Fd = fd;
}
void Client::setIpAdd(std::string ipadd) {
    this->IPadd = ipadd;
}
std::string Client::GetRealname() const {
    return this->Realname;
}
void Client::SetRealname(const std::string& realname) {
    this->Realname = realname;
}