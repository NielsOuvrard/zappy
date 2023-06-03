/*
** EPITECH PROJECT, 2023
** network
** File description:
** network
*/

#pragma once
#include "zappy_gui.hpp"

class Network
{
public:
    Network(char *ip, int port);
    ~Network();
    int get_sock() const { return _sock; }
    char *get_ip() const { return _ip; }
    int get_port() const { return _port; }
    // void set_sock(int sock) { _sock = sock; }
    // void set_ip(char *ip) { _ip = ip; }
    // void set_port(int port) { _port = port; }
    void send_data(std::string data);
    std::string receive_data();
    char *get_message();

private:
    int _sock;
    char *_ip;
    int _port;
};
