/*
** EPITECH PROJECT, 2023
** net
** File description:
** et
*/

#include "Network.hpp"
#include <sys/select.h>

Network::Network(char *ip, int port) : _ip(ip), _port(port)
{
    struct sockaddr_in server;
    _sock = socket(AF_INET, SOCK_STREAM, 0);
    if (_sock < 0)
    {
        std::cout << "Socket failed" << std::endl;
        exit(84);
    }
    server.sin_addr.s_addr = inet_addr(ip);
    server.sin_family = AF_INET;
    server.sin_port = htons(port);
    if (connect(_sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        std::cout << "Connection failed" << std::endl;
        exit(84);
    }
}

Network::~Network()
{
    close(_sock);
}

void Network::send_data(std::string data)
{
    send(_sock, data.c_str(), data.length(), 0);
}

// faire select

std::string Network::receive_data()
{
    int size_str = 0, len = 0;
    char buff[4096];
    memset(buff, 0, 4096);
    std::string data = "";
    while (size_str == 0 || buff[size_str - 1] != '\n')
    {
        FD_ZERO(&_readfds);
        FD_SET(_sock, &_readfds);
        select(_sock + 1, &_readfds, NULL, NULL, NULL);
        len = read(_sock, buff + size_str, 1);
        if (len == 0)
        {
            std::cout << "Server disconnected" << std::endl;
            close(_sock);
            throw std::runtime_error("Server disconnected");
        }
        else if (len < 0)
        {
            usleep(1000);
            if (errno == 9)
            {
                std::cout << "Server disconnected" << std::endl;
                close(_sock);
                throw std::runtime_error("Server disconnected");
            }
        }
        else
        {
            size_str += len;
        }
    }
    if (len < 0 || buff[0] == '\0')
        return "";
    data = buff;
    return data;
}
