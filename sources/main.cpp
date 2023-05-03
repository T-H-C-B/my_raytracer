//
// Created by Clément Lagasse on 26/04/2023.
//

#include <iostream>
#include "Core.hpp"

int main(int ac, char **av)
{
    std::string graphLib = "SFMLGraph";
    if (ac == 2) {
        if (av[1] == std::string("-h") || av[1] == std::string("-help")) {
            std::cout << "USAGE: ./RayTracer [GRAPHIC_LIBRARY]" << std::endl;
            std::cout << "GRAPHIC_LIBRARY: SFMLGraph, PocGraph" << std::endl;
            return 0;
        }
        graphLib = av[1];
    }
    RayTracer::Core::Core core(graphLib);
    return core.run();
}
