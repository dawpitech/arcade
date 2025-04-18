/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** MainMenu.cpp
*/

#include <algorithm>

#include "../Arcade.hpp"
#include "../utils/KeysToAscii.hpp"
#include "../utils/ScoreStorage.hpp"
#include "ANAL/IModule.hpp"
#include "MainMenu.hpp"

void MainMenu::processEvents(std::vector<ANAL::Event>& events)
{
    for (const auto &[type, keyEvent, mouseEvent, closeEvent] : events) {
        if (type != ANAL::EventType::KEYBOARD)
            continue;
        if (keyEvent->key == ANAL::Keys::ARROW_DOWN && keyEvent->state == ANAL::State::PRESSED)
            this->selected_index++;
        if (keyEvent->key == ANAL::Keys::ARROW_UP && keyEvent->state == ANAL::State::PRESSED)
            this->selected_index--;
        if (keyEvent->key == ANAL::Keys::ARROW_LEFT && keyEvent->state == ANAL::State::PRESSED)
            this->selected_chr--;
        if (keyEvent->key == ANAL::Keys::ARROW_RIGHT && keyEvent->state == ANAL::State::PRESSED)
            this->selected_chr++;
        if (keyEvent->key == ANAL::Keys::SPECIAL_KEY_ENTER && keyEvent->state == ANAL::State::PRESSED && selected_chr == 0)
            this->enter = true;
        if (keyEvent->state == ANAL::State::PRESSED && selected_chr > 0) {
            if (const char chr = analUtils::analKeyToAscii(keyEvent->key); chr != '?')
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
    this->selected_chr = std::clamp(this->selected_chr, 1, 4);

    if (init)
        this->_playername = arcade.getPlayerName();
    this->init = false;
    my_arcade.setPlayername(this->_playername);

    if (!this->enter)
        return;
    if (selected_index < my_arcade.getGamesList().size()) {
        my_arcade.launchGame(this->selected_game);
        return;
    }
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
        if (this->_playername == "????")
            this->_playername = "    ";
        renderer.drawText("^", ANAL::Vector2(1 + selected_chr, 8 + games_len + renderers_len));
    }

    if (this->selected_chr == 0 && this->_playername == "    ")
        this->_playername = "????";

    for (int i = 0; i < 4; i++)
        renderer.drawText(std::string{this->_playername.at(i)}, ANAL::Vector2(2 + i, 7 + games_len + renderers_len));

    if (this->_playername == "????" || this->_playername == "    ") {
        renderer.drawText("Careful ! without a name your score", ANAL::Vector2(6, 9 + games_len + renderers_len));
        renderer.drawText("won't be saved", ANAL::Vector2(11, 10 + games_len + renderers_len));
    }

    renderer.drawText("PRO TIPS:", ANAL::Vector2(13, 21));
    renderer.drawText("You can press 'N' to switch to the next game", ANAL::Vector2(5, 22));
    renderer.drawText("You can press 'B' to switch renderer", ANAL::Vector2(7, 23));
    renderer.drawText("You can press 'R' to restart a game", ANAL::Vector2(7, 24));
    renderer.drawText("You can press 'M' to go back to the menu", ANAL::Vector2(6, 25));
    renderer.drawText("You can press 'Q' to quit", ANAL::Vector2(9, 26));

    renderer.drawText("Last score:", ANAL::Vector2(13, 28));
    renderer.drawText(std::to_string(SaveFile::loadScore(my_arcade.getLastGameName(), this->_playername)), ANAL::Vector2(14, 29));

    renderer.render();
}

ANAL::ModuleVersion uwu_get_module_version()
    { return ANAL::ModuleVersion::V1_1_0; }

ANAL::ModuleType uwu_get_module_type()
    { return ANAL::ModuleType::GAME; }

std::unique_ptr<ANAL::IGame> uwu_entrypoint_game()
    { return std::make_unique<MainMenu>(); }
