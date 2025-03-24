/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** main.cpp
*/

#include <iostream>
#include <ostream>

#include "Arcade.hpp"
#include "menu/MainMenu.hpp"
#include "utils/ModuleLoader.hpp"

int main(const int argc, const char** argv)
{
    Arcade arcade;
    std::unique_ptr<ANAL::IGame> menu = std::make_unique<MainMenu>();

    if (argc != 2)
        return Arcade::printHelp(), EXIT_FAILURE_TECH;
    try
    {
        arcade._renderer_so_handle = SafeDL::open(argv[1], RTLD_LAZY);
        if (ModuleLoader::getModuleType(arcade._renderer_so_handle) != ANAL::ModuleType::RENDERER)
            throw std::exception();
        auto renderer = ModuleLoader::loadRenderer(arcade._renderer_so_handle);
        arcade.setRenderer(renderer);
        arcade.setGame(menu);
    }
    catch (std::exception& e)
    {
        std::cerr << "arcade: " << e.what() << std::endl;
        return EXIT_FAILURE_TECH;
    }
    arcade.launch();
    return EXIT_SUCCESS;
}
