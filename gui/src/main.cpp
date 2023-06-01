/*
** EPITECH PROJECT, 2021
** zappy_gui
** File description:
** zappy_gui
*/

#include "zappy_gui.hpp"

int help(void)
{
    std::cout << "USAGE: ./zappy_gui -p port -h machine" << std::endl;
    std::cout << "\tport\tis the port number" << std::endl;
    std::cout << "\tmachine\tis the name of the machine; localhost by default" << std::endl;
    return 0;
}

int main(int ac, char **av)
{
    if ((ac == 2 && std::string(av[1]) == "-h") || (ac == 2 && std::string(av[1]) == "-help"))
        return help();
    return zappy_gui(ac, av);
}
