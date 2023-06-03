/*
** EPITECH PROJECT, 2023
** net
** File description:
** et
*/

#include "network.hpp"
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

std::string Network::receive_data()
{
    char buffer[1024];
    memset(buffer, 0, 1024);
    int valread = read(_sock, buffer, 1024);
    if (valread < 0)
    {
        std::cout << "Read failed" << std::endl;
        // exit(84);
    }
    if (valread == 0)
    {
        std::cout << "Server disconnected" << std::endl;
        close(_sock);
        exit(84);
    }
    if (buffer[0] == '\0')
        return "";
    std::string data = buffer;
    return data;
}

// useless ?
char *Network::get_message()
{
    fd_set readFds;
    fd_set writeFds;
    timeval tv;

    char *buffer = new char[4096];

    tv.tv_sec = 0;
    tv.tv_usec = 0;
    FD_ZERO(&readFds);
    FD_SET(_sock, &readFds);
    select(_sock + 1, &readFds, &writeFds, NULL, &tv);
    if (FD_ISSET(_sock, &readFds))
    {
        memset(buffer, 0, 4096);
        if (recv(_sock, buffer, 4096, 0) <= 0)
        {
            std::cout << "Server disconnected" << std::endl;
            close(_sock);
            exit(84);
        }
        std::cout << buffer << std::endl;
        return buffer;
    }
    std::cout << "No message" << std::endl;
    delete[] buffer;
    return NULL;
}
