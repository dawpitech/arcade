/*
** EPITECH PROJECT, 2025
** Snake
** File description:
** uwu
*/

#include <algorithm>
#include <random>
#include <string>

#include "Snake.hpp"
#include "ANAL/Events.hpp"
#include "ANAL/IArcade.hpp"
#include "ANAL/IModule.hpp"
#include "ANAL/Vector2.hpp"

void arcade::games::Snake::moveBerryRandom()
{
    this->_berryPos = {
        std::uniform_int_distribution{2, 29}(this->_rng),
        std::uniform_int_distribution{3, 29}(this->_rng)
    };
}

void arcade::games::Snake::init()
{
    this->_playerName = "";
    this->_gameEnded = false;
    this->_bestScore = -1;
    this->_score = 0;
    this->moveBerryRandom();
    this->_currentMap = MAP;
    this->_snake.clear();
    this->_snake.emplace_back(15, 15);
    this->_direction = {1, 0};
    this->_currentMap[15][15] = '@';
}

void arcade::games::Snake::processEvents(std::vector<ANAL::Event> &ev)
{
    for (auto &[type, keyEvent, mouseEvent, closeEvent] : ev)
    {
        if (type == ANAL::EventType::KEYBOARD)
        {
            const auto key = keyEvent->key;
            if (key == ANAL::Keys::ARROW_UP && _direction.y == 0)
                _direction = {0, -1};
            if (key == ANAL::Keys::ARROW_DOWN && _direction.y == 0)
                _direction = {0, 1};
            if (key == ANAL::Keys::ARROW_LEFT && _direction.x == 0)
                _direction = {-1, 0};
            if (key == ANAL::Keys::ARROW_RIGHT && _direction.x == 0)
                _direction = {1, 0};
            if (key == ANAL::Keys::KEY_R && this->_gameEnded)
                this->restart();
        }
    }
}

void arcade::games::Snake::compute(ANAL::IArcade &arcade)
{
    if (this->_playerName.empty())
        this->_playerName = arcade.getPlayerName();
    if (this->_bestScore == -1)
        this->_bestScore = arcade.getPlayerHighscore(this->_playerName);
    if (this->_score > this->_bestScore && this->_gameEnded)
    {
        this->_bestScore = this->_score;
        arcade.setPlayerHighscore(this->_bestScore);
    }
    if (this->_gameEnded)
        return;

    static int frame = 0;
    if (++frame < 5)
        return;
    frame = 0;

    auto new_head = _snake.front();
    new_head.x += _direction.x;
    new_head.y += _direction.y;

    bool hit_self = false;
    for (const auto &segment : _snake)
    {
        if (segment.x == new_head.x && segment.y == new_head.y)
        {
            hit_self = true;
            break;
        }
    }
    if (_currentMap[new_head.y][new_head.x - 1] == '#' || hit_self)
    {
        _gameEnded = true;
        return;
    }
    _snake.push_front(new_head);
    if (new_head.x == _berryPos.x && new_head.y == _berryPos.y)
    {
        _score += 100;
        do
            this->moveBerryRandom();
        while (_currentMap[_berryPos.y][_berryPos.x - 1] != ' ');
    }
    else
    {
        const auto tail = _snake.back();
        _currentMap[tail.y][tail.x - 1] = ' ';
        _snake.pop_back();
    }
    _currentMap[new_head.y][new_head.x - 1] = '+';
}

void arcade::games::Snake::render(ANAL::IRenderer &renderer, const ANAL::IArcade &arcade)
{
    renderer.clear();
    renderer.setWindowTitle("Snake");
    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 30; j++)
        {
            auto const map_e = arcade.newEntity();
            auto const map_a = arcade.newAsset();
            std::string tile = "./assets/Snake/textures/";
            switch (this->_currentMap[i][j])
            {
                case '#':
                    tile += "wall.png";
                    break;
                default:
                    tile = "";
                    break;
            }
            if (!tile.empty())
            {
                map_a->setTexturePath(tile);
                map_a->setAlternateRender(this->_currentMap[i][j]);
                map_e->setPos(ANAL::Vector2(j + 1, i));
                map_e->setAsset(*map_a);
                renderer.drawEntity(*map_e);
            }
        }
    }
    auto const berry_e = arcade.newEntity();
    auto const berry_a = arcade.newAsset();
    berry_a->setTexturePath("./assets/Snake/textures/berry.png");
    berry_a->setAlternateRender('@');
    berry_e->setPos(this->_berryPos);
    berry_e->setAsset(*berry_a);
    renderer.drawEntity(*berry_e);
    renderer.drawText("Player: " + this->_playerName, ANAL::Vector2(1, 0));
    renderer.drawText("Score: " + std::to_string(this->_score), ANAL::Vector2(1, 1));
    renderer.drawText("Best: " + std::to_string(this->_bestScore), ANAL::Vector2(20, 1));
    for (auto &segment : _snake)
    {
        auto seg_e = arcade.newEntity();
        auto seg_a = arcade.newAsset();
        seg_a->setTexturePath("./assets/Snake/textures/snake.png");
        seg_a->setAlternateRender('o');
        seg_e->setPos(segment);
        seg_e->setAsset(*seg_a);
        renderer.drawEntity(*seg_e);
    }
    static int frame = 0;
    frame++;
    if (this->_gameEnded)
    {
        if ((frame / 20) % 2 == 0)
        {
            renderer.drawText(" arcade::games::Snake Over", ANAL::Vector2(13, 13));
            renderer.drawText("Player: " + this->_playerName, ANAL::Vector2(13, 14));
            renderer.drawText("Score: " + std::to_string(this->_score), ANAL::Vector2(13, 15));
            renderer.drawText("Best: " + std::to_string(this->_bestScore), ANAL::Vector2(13, 16));
            renderer.drawText("Press R to restart", ANAL::Vector2(12, 17));
        }
    }
    if (frame >= 6000)
        frame = 0;
    renderer.render();
}

extern "C" std::unique_ptr<ANAL::IGame> uwu_entrypoint_game(void) { return std::make_unique<arcade::games::Snake>(); }

ANAL::ModuleVersion uwu_get_module_version() { return ANAL::ModuleVersion::V1_1_0; }

ANAL::ModuleType uwu_get_module_type() { return ANAL::ModuleType::GAME; }
