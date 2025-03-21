/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** MainMenu.cpp
*/

#include "MainMenu.hpp"

#include <iostream>

void MainMenu::processEvents(const std::vector<anal::Event>&)
{
    std::cout << "MainMenu is processing Events" << std::endl;
}

void MainMenu::compute()
{
    std::cout << "MainMenu is computing" << std::endl;
}

void MainMenu::render()
{
    std::cout << "MainMenu is rendering" << std::endl;
}

std::unique_ptr<anal::IGame> uwu_entrypoint_renderer()
    { return std::make_unique<MainMenu>(); }

std::unique_ptr<anal::IModule> uwu_entrypoint_module()
    { return std::make_unique<MainMenu>(); }
