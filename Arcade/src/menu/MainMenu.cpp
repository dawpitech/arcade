/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** MainMenu.cpp
*/

#include <algorithm>

#include "MainMenu.hpp"
#include "../Arcade.hpp"
#include "ANAL/IModule.hpp"

void MainMenu::processEvents(std::vector<ANAL::Event>& events)
{
    for (const auto &[type, keyEvent, mouseEvent, closeEvent] : events) {
        if (type == ANAL::EventType::KEYBOARD && keyEvent.value().key == ANAL::Keys::ARROW_DOWN && keyEvent.value().state == ANAL::State::PRESSED)
            this->selected_game++;
        if (type == ANAL::EventType::KEYBOARD && keyEvent.value().key == ANAL::Keys::ARROW_UP && keyEvent.value().state == ANAL::State::PRESSED)
            this->selected_game--;
        if (type == ANAL::EventType::KEYBOARD && keyEvent.value().key == ANAL::Keys::KEY_E && keyEvent.value().state == ANAL::State::PRESSED)
            this->launching = true;
    }

    events.clear();
}

void MainMenu::compute()
{
}

void MainMenu::render(ANAL::IRenderer& renderer, const ANAL::IArcade& arcade)
{
    const auto& my_arcade = dynamic_cast<const Arcade&>(arcade);
    this->selected_game = std::clamp(this->selected_game, 0, static_cast<int>(my_arcade.getGamesList().size()) - 1);

    if (this->launching) {
        const_cast<Arcade&>(my_arcade).launchGame(this->selected_game);
        return;
    }

    renderer.clear();
    renderer.setWindowTitle("Main Menu - Arcade");
    renderer.drawText("Arcade menu", ANAL::Vector2(12, 0));
    renderer.drawText("Choose game:", ANAL::Vector2(0, 2));

    int vertical_index = 3;
    for (const auto& game : my_arcade.getGamesList())
        renderer.drawText(game, ANAL::Vector2(2, vertical_index++));

    renderer.drawText("->", ANAL::Vector2(0, 3 + selected_game));

    renderer.drawText("PRO TIPS:", ANAL::Vector2(13, 20));
    renderer.drawText("You can press 'N' to switch to the next game", ANAL::Vector2(5, 21));
    renderer.drawText("You can press 'B' to switch renderer", ANAL::Vector2(7, 22));

    renderer.render();
}

ANAL::ModuleVersion uwu_get_module_version()
    { return ANAL::ModuleVersion::V1_1_0; }

ANAL::ModuleType uwu_get_module_type()
    { return ANAL::ModuleType::GAME; }

std::unique_ptr<ANAL::IGame> uwu_entrypoint_game()
    { return std::make_unique<MainMenu>(); }
