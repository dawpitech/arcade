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
    std::unique_ptr<anal::IGame> menu = std::make_unique<MainMenu>();

    if (argc != 2)
        return Arcade::printHelp(), EXIT_FAILURE_TECH;
    try
    {
        arcade._renderer_so_handle = SafeDL::open(argv[1], RTLD_LAZY);
        const auto module = ModuleLoader::loadModule(arcade._renderer_so_handle);
        if (module->getModuleType() != anal::IModule::ModuleType::RENDERER)
            throw std::exception();
        auto* rawRenderer = dynamic_cast<anal::IRenderer*>(module.get());
        //TODO: check dyn cast
        std::unique_ptr<anal::IRenderer> renderer(rawRenderer);
        arcade.setRenderer(std::move(renderer));
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
