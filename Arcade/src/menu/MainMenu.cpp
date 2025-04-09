/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** MainMenu.cpp
*/

#include <algorithm>

#include "../utils/KeysToAscii.hpp"
#include "MainMenu.hpp"
#include "../Arcade.hpp"
#include "ANAL/IModule.hpp"

void MainMenu::processEvents(std::vector<ANAL::Event>& events)
{
    for (const auto &[type, keyEvent, mouseEvent, closeEvent] : events) {
        if (type != ANAL::EventType::KEYBOARD)
            continue;
        if (keyEvent.value().key == ANAL::Keys::ARROW_DOWN && keyEvent.value().state == ANAL::State::PRESSED)
            this->selected_index++;
        if (keyEvent.value().key == ANAL::Keys::ARROW_UP && keyEvent.value().state == ANAL::State::PRESSED)
            this->selected_index--;
        if (keyEvent.value().key == ANAL::Keys::ARROW_LEFT && keyEvent.value().state == ANAL::State::PRESSED)
            this->selected_chr--;
        if (keyEvent.value().key == ANAL::Keys::ARROW_RIGHT && keyEvent.value().state == ANAL::State::PRESSED)
            this->selected_chr++;
        if (keyEvent.value().key == ANAL::Keys::KEY_E && keyEvent.value().state == ANAL::State::PRESSED && selected_chr == 0)
            this->enter = true;
        if (keyEvent.value().state == ANAL::State::PRESSED && selected_chr > 0) {
            if (const char chr = analUtils::analKeyToAscii(keyEvent.value().key); chr != '?')
                this->_playername.at(selected_chr++ - 1) = chr;
            if (selected_chr > 4)
                selected_chr = 4;
        }
    }

    events.clear();
}

void MainMenu::compute(ANAL::IArcade& arcade)
{
    auto& my_arcade = dynamic_cast<Arcade&>(arcade);
    this->selected_index = std::clamp(this->selected_index, 0,
        static_cast<int>(my_arcade.getGamesList().size() + my_arcade.getRenderersList().size()));
    this->selected_chr = std::clamp(this->selected_chr, 0, 4);

    my_arcade.setPlayername(this->_playername);

    if (!this->enter)
        return;
    if (selected_index < my_arcade.getGamesList().size())
        my_arcade.launchGame(this->selected_game);
    else
        my_arcade.setRenderer(this->selected_renderer);
    this->enter = false;
}

void MainMenu::render(ANAL::IRenderer& renderer, const ANAL::IArcade& arcade)
{
    const auto& my_arcade = dynamic_cast<const Arcade&>(arcade);
    const auto& renderers_len = static_cast<int>(my_arcade.getRenderersList().size());
    const auto& games_len = static_cast<int>(my_arcade.getGamesList().size());

    renderer.clear();
    renderer.setWindowTitle("Main Menu - Arcade");
    renderer.drawText("Arcade menu", ANAL::Vector2(12, 0));

    renderer.drawText("Choose game:", ANAL::Vector2(0, 2));
    int vertical_index = 3;
    for (const auto& game : my_arcade.getGamesList())
        renderer.drawText(game, ANAL::Vector2(2, vertical_index++));

    renderer.drawText("Choose renderer:", ANAL::Vector2(0, ++vertical_index));
    vertical_index++;
    for (const auto& renderer_entry : my_arcade.getRenderersList())
        renderer.drawText(renderer_entry, ANAL::Vector2(2, vertical_index++));

    if (selected_index < my_arcade.getGamesList().size()) {
        renderer.drawText("->", ANAL::Vector2(0, 3 + selected_index));
        selected_game = selected_index;
        this->selected_chr = 0;
    } else if (selected_index < games_len + renderers_len) {
        renderer.drawText("->", ANAL::Vector2(0, 2 + selected_index + renderers_len));
        selected_renderer = selected_index - games_len;
        this->selected_chr = 0;
    } else if (this->selected_chr > 0) {
        renderer.drawText("^", ANAL::Vector2(1 + selected_chr, 8 + games_len + renderers_len));
    } else {
        renderer.drawText("-> ", ANAL::Vector2(0,  7 + games_len + renderers_len));
    }

    for (int i = 0; i < 4; i++)
        renderer.drawText(std::string{this->_playername.at(i)}, ANAL::Vector2(2 + i, 7 + games_len + renderers_len));

    renderer.drawText("PRO TIPS: (disabled for now)", ANAL::Vector2(13, 23));
    renderer.drawText("You can press 'N' to switch to the next game", ANAL::Vector2(5, 24));
    renderer.drawText("You can press 'B' to switch renderer", ANAL::Vector2(7, 25));

    renderer.render();
}

ANAL::ModuleVersion uwu_get_module_version()
    { return ANAL::ModuleVersion::V1_1_0; }

ANAL::ModuleType uwu_get_module_type()
    { return ANAL::ModuleType::GAME; }

std::unique_ptr<ANAL::IGame> uwu_entrypoint_game()
    { return std::make_unique<MainMenu>(); }
