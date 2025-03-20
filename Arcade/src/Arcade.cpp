/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** Arcade.cpp
*/

#include <iostream>

#include "Arcade.hpp"
#include "utils/ModuleLoader.hpp"

int printHelp()
{
    std::cout << "USAGE: ./arcade </path/to/a/renderer.so>" << std::endl;
    return EXIT_FAILURE_TECH;
}

int main(const int argc, const char** argv)
{
    if (argc != 2)
        return printHelp();
    try
    {
        const SafeDL::safeHandle handle = SafeDL::open(argv[1], RTLD_LAZY);
        const std::unique_ptr<anal::IModule> module = ModuleLoader::loadModule(handle);
        std::cout << "Doing things" << std::endl;
    }
    catch (std::exception& e)
    {
        std::cerr << "arcade: " << e.what() << std::endl;
        return EXIT_FAILURE_TECH;
    }
    return EXIT_SUCCESS;
}
