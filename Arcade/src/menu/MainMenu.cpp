/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** MainMenu.cpp
*/

#include "MainMenu.hpp"

#include <iostream>

void MainMenu::processEvents(const std::vector<ANAL::Event>&)
{
    std::cout << "MainMenu is processing Events" << std::endl;
}

void MainMenu::compute()
{
    std::cout << "MainMenu is computing" << std::endl;
}

void MainMenu::render(ANAL::IRenderer& renderer)
{
    std::cout << "MainMenu is rendering" << std::endl;
}

ANAL::ModuleVersion uwu_get_module_version()
{ return ANAL::ModuleVersion::V1_1_0; }

ANAL::ModuleType uwu_get_module_type()
{ return ANAL::ModuleType::GAME; }

std::unique_ptr<ANAL::IGame> uwu_entrypoint_game()
    { return std::make_unique<MainMenu>(); }
