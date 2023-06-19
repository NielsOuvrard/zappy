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

// std::string Network::receive_data()
// {
//     char buffer[4096];
//     memset(buffer, 0, 4096);
//     int valread = read(_sock, buffer, 4095);
//     std::string data = "";
//     if (valread < 0)
//     {
//         std::cout << "Read failed" << std::endl;
//         std::cout << errno << std::endl; // 9 = bad file descriptor
//     }
//     else if (valread == 0)
//     {
//         std::cout << "Server disconnected" << std::endl;
//         close(_sock);
//         exit(84);
//     }
//     if (buffer[0] == '\0')
//         return "";
//     data = buffer;
//     return data;
// }

std::string Network::receive_data()
{
    int size_str = 0;
    int len = 0;
    char buff[4096];
    std::string data = "";
    while ((len = read(_sock, buff + size_str, 1)) > 0 && buff[size_str + len - 1] != '\n')
        size_str += len;
    if (len < 0 || buff[0] == '\0')
        return "";
    data = buff;

    // std::cout << "data: " << data << std::endl;

    return data;
}
//     char buffer[4096];
//     memset(buffer, 0, 4096);
//     std::string data = "";
//     // buffer handling with \n check
//     int valread = 0;
//     while ((valread = read(_sock, buffer, 4095)) > 0 && buffer[strlen(buffer) - 1] != '\n')
//     {
//         data = data + buffer;
//         memset(buffer, 0, 4096);
//     }
//     if (valread < 0)
//     {
//         std::cout << "Read failed" << std::endl;
//         std::cout << errno << std::endl; // 9 = bad file descriptor
//     }
//     else if (valread == 0)
//     {
//         std::cout << "Server disconnected" << std::endl;
//         close(_sock);
//         exit(84);
//     }
//     if (buffer[0] == '\0')
//         return "";
//     return data;
// }
