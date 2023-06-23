/*
** EPITECH PROJECT, 2021
** zappy_gui
** File description:
** zappy_gui
*/

#include "zappy_gui.hpp"
#include "Network.hpp"
#include "Gui.hpp"
#include "Mutex.hpp"
#include "Pthread.hpp"
#include "Menu.hpp"
#include <sys/select.h>

typedef struct args_s
{
    int port;
    char *machine;
} args_t;

typedef struct shared_s
{
    Network *net;
    Gui *gui;
    std::string data;
    bool stop;
} shared_t;

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

void *thread_net_func(void *arg)
{
    shared_t *shared = (shared_t *)arg;
    while (!shared->stop)
    {
        try {
            shared->gui->fill_map(shared->data);
            shared->data = shared->net->receive_data();
        } catch (std::runtime_error &e) {
            std::cout << e.what() << std::endl;
            shared->stop = true;
        }
    }
    pthread_exit(EXIT_SUCCESS);
    return NULL;
}

int zappy_gui(int ac, char **av)
{
    args_t args = get_arguments(ac, av);
    shared_t shared;
    Menu menu(args.machine, std::to_string(args.port));
    menu.menu_run();
    args.machine = (char *)menu.get_ip().c_str();
    args.port = atoi(menu.get_port().c_str());
    Network net(args.machine, args.port);
    shared.net = &net;
    MyPthread thread_net;

    shared.data = shared.net->receive_data(); // WELECOME
    shared.net->send_data("GRAPHIC\n");
    shared.data = shared.net->receive_data();
    Gui gui(shared.data, &net, &shared.stop);
    shared.gui = &gui;
    shared.stop = false;

    thread_net.create(thread_net_func, &shared);


    gui.run();
    shared.stop = true;

    std::cout << "END" << std::endl;
    return 0;
}
