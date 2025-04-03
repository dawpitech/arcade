/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** MainMenu.cpp
*/

#include <iostream>

#include "MainMenu.hpp"
#include "ANAL/IModule.hpp"

void MainMenu::processEvents(std::vector<ANAL::Event>& events)
{
    while (!events.empty()) {
        //const auto event = events.back();
        events.pop_back();
    }
}

void MainMenu::compute()
{
}

void MainMenu::render(ANAL::IRenderer& renderer, const ANAL::IArcade& arcade)
{
    renderer.clear();
    renderer.setWindowTitle("Main Menu - Arcade");
    renderer.drawText("Arcade menu", ANAL::Vector2(0, 0));
    renderer.drawText("Choose game:", ANAL::Vector2(0, 2));
    renderer.drawText("-> Minesweeper", ANAL::Vector2(1, 3));
    auto const entity = arcade.newEntity();
    auto const asset = arcade.newAsset();
    asset->setTexturePath("./assets/textures/test.png");
    asset->setAlternateRender('X');
    entity->setPos(ANAL::Vector2(0, 0));
    entity->setAsset(*asset);
    renderer.drawEntity(*entity);
    renderer.render();
}

ANAL::ModuleVersion uwu_get_module_version()
    { return ANAL::ModuleVersion::V1_1_0; }

ANAL::ModuleType uwu_get_module_type()
    { return ANAL::ModuleType::GAME; }

std::unique_ptr<ANAL::IGame> uwu_entrypoint_game()
    { return std::make_unique<MainMenu>(); }
