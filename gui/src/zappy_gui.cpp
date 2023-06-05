/*
** EPITECH PROJECT, 2021
** zappy_gui
** File description:
** zappy_gui
*/

#include "zappy_gui.hpp"
#include "network.hpp"
#include "gui.hpp"
#include <sys/select.h>

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

int zappy_gui(int ac, char **av)
{
    args_t args = get_arguments(ac, av);
    Network net(args.machine, args.port);
    std::string data = net.receive_data(); // Welcome
    net.send_data("GRAPHIC\n");
    data = net.receive_data();
    Gui gui(data);
    while (!gui.fill_map(data))
    {
        net.send_data("mct\n");
        data = net.receive_data();
    }

    gui.run();
    std::cout << "END" << std::endl;
    return 0;
}
