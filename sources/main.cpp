//
// Created by Clément Lagasse on 26/04/2023.
//

#include <iostream>
#include "Core.hpp"
#include "Parameters.hpp"

bool hasArg(std::string arg, int ac, char **av)
{
    for (int i = 0; i < ac; i++) {
        if (av[i] == arg)
            return true;
    }
    return false;
}

int main(int ac, char **av)
{
    std::string graphLib = "SFMLGraph";
    if (ac >= 2) {
        if (av[1] == std::string("-h") || av[1] == std::string("-help")) {
            std::cout << "USAGE: ./RayTracer [GRAPHIC_LIBRARY]" << std::endl;
            std::cout << "GRAPHIC_LIBRARY: SFMLGraph, PocGraph" << std::endl;
            return 0;
        }
        graphLib = av[1];
    }
    RayTracer::Core::Core core(graphLib);
    if (hasArg("--test", ac, av)) {
        Parameters::getInstance().setSeed(42);
        Parameters::getInstance().setNumOcclusionRays(1);
        Parameters::getInstance().setNumShadowRays(1);
    } else {
        Parameters::getInstance().setSeed(static_cast<unsigned int>(time(nullptr)));
        Parameters::getInstance().setNumOcclusionRays(5);
        Parameters::getInstance().setNumShadowRays(10);
    }
    return core.run();
}
