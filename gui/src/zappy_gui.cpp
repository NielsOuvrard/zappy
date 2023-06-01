/*
** EPITECH PROJECT, 2021
** zappy_gui
** File description:
** zappy_gui
*/

#include "zappy_gui.hpp"

// USAGE: ./zappy_ai -p port -h machine
// port is the port number
// machine is the name of the machine; localhost by default

typedef struct args_s
{
    int port;
    char *machine;
} args_t;

args_t get_arguments(int ac, char **av)
{
    args_t args = {0, NULL};

    for (int i = 1; i < ac; i += 2)
    {
        if (std::string(av[i]) == "-p")
        {
            args.port = atoi(av[i + 1]);
        }
        else if (std::string(av[i]) == "-h")
        {
            args.machine = av[i + 1];
        }
        else
        {
            std::cout << "Unknown argument: " << av[i] << std::endl;
            help();
            exit(84);
        }
    }
    return args;
}

int server_connection(args_t args)
{
    std::cout << "port: " << args.port << std::endl;
    std::cout << "machine: " << args.machine << std::endl;
    std::string ip = args.machine;
    struct sockaddr_in server;
    int sock = socket(AF_INET, SOCK_STREAM, 0);
    server.sin_addr.s_addr = inet_addr(ip.c_str());
    server.sin_family = AF_INET;
    server.sin_port = htons(args.port);
    if (connect(sock, (struct sockaddr *)&server, sizeof(server)) < 0)
    {
        std::cout << "Connection failed" << std::endl;
        return 84;
    }
    std::cout << "Connected" << std::endl;
    return sock;
}

int zappy_gui(int ac, char **av)
{
    args_t args = get_arguments(ac, av);
    int sock = server_connection(args);
    if (!sock)
        return 84;
    char buffer[1024] = {0};
    int valread = read(sock, buffer, 1024);
    if (valread < 0)
    {
        std::cout << "Read failed" << std::endl;
        return 84;
    }
    std::cout << buffer << std::endl;
    // write(sock, "msz", 3);
    send(sock, "msz\n", 3, 0);
    while ((valread = read(sock, buffer, 1024)))
    {
        if (valread < 0)
        {
            std::cout << "Read failed" << std::endl;
            return 84;
        }
        std::cout << buffer << std::endl;
    }
    close(sock);
    std::cout << "END" << std::endl;
    return 0;
}

// {
//     for (int i = 0; i < ac; i++)
//     {
//         std::cout << av[i] << std::endl;
//     }

//     sf::RenderWindow window(sf::VideoMode(800, 600), "Zappy");
//     // sf::CircleShape shape(100.f);
//     // shape.setFillColor(sf::Color::Green);
//     while (window.isOpen())
//     {
//         sf::Event event;
//         while (window.pollEvent(event))
//         {
//             if (event.type == sf::Event::Closed)
//             {
//                 window.close();
//             }
//             else
//             {
//                 std::cout << "Event type: " << event.type << std::endl;
//             }
//         }
//         window.clear();
//         // window.draw(shape);
//         window.display();
//     }

//     return 0;
// }
