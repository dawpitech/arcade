/*
** EPITECH PROJECT, 2025
** Pacman
** File description:
** uwu
*/

#include "Pacman.hpp"
#include <algorithm>
#include <iostream>
#include <random>
#include <string>
#include <vector>
#include "ANAL/Events.hpp"
#include "ANAL/IModule.hpp"
#include "ANAL/Vector2.hpp"



void arcade::games::Pacman::deinit() { this->_ghosts.clear(); }

void arcade::games::Pacman::init()
{
    this->_player = Player();
    this->_playername.clear();
    this->_currentMap = MAP;
    this->_ghostsTime = 200;
    this->_ghosts.emplace_back(ANAL::Vector2(15, 14), "red");
    this->_ghosts.emplace_back(ANAL::Vector2(16, 14), "blue");
    this->_ghosts.emplace_back(ANAL::Vector2(15, 16), "pink");
    this->_ghosts.emplace_back(ANAL::Vector2(16, 16), "orange");
}

void arcade::games::Pacman::restart()
{
    this->deinit();
    this->init();
}

arcade::games::Pacman::Pacman()
{
    this->_bestScore = -1;
    this->init();
}

arcade::games::Pacman::~Pacman() { this->deinit(); }

void arcade::games::Pacman::processEvents(std::vector<ANAL::Event> &ev)
{
    static int frame = 0;
    static int add_x = 0;
    static int add_y = 0;

    for (const auto &[type, keyEvent, mouseEvent, closeEvent] : ev)
    {
        if (type != ANAL::EventType::KEYBOARD)
            continue;
        const auto key = keyEvent.value().key;
        const auto down = keyEvent.value().state == ANAL::State::RELEASED;

        switch (key) {
            case ANAL::Keys::ARROW_UP:
                add_y = down ? 0 : -1;
                break;
            case ANAL::Keys::ARROW_DOWN:
                add_y = down ? 0 : +1;
                break;
            case ANAL::Keys::ARROW_LEFT:
                add_x = down ? 0 : -1;
                this->_player.setLook(Player::LEFT);
                break;
            case ANAL::Keys::ARROW_RIGHT:
                add_x = down ? 0 : +1;
                this->_player.setLook(Player::RIGHT);
                break;
            case ANAL::Keys::KEY_R:
                if (this->_player.getState() != Player::DEAD)
                    continue;
                this->restart();
                break;
            default:
                break;
        }
    }
    if (frame++ < 1 || this->_player.getState() == Player::DEAD)
        return;
    frame = 0;
    const int new_x = this->_player.getPos().x + add_x - 1;
    const int new_y = this->_player.getPos().y + add_y;
    if (this->_currentMap[new_y][new_x] == '#' || this->_currentMap[new_y][new_x] == '_')
        return;
    if (this->_currentMap[new_y][new_x] == '.')
    {
        this->_currentMap[new_y][new_x] = ' ';
        this->_player.setScore(this->_player.getScore() + 100);
    }
    if (this->_currentMap[new_y][new_x] == 'o')
    {
        this->_currentMap[new_y][new_x] = ' ';
        this->_player.setScore(this->_player.getScore() + 1000);
        this->_player.tickReset();
        this->_player.setState(Player::HIGH);
    }
    if (this->_currentMap[new_y][new_x] == '!')
    {
        if (this->_player.getPos().x + add_x == 29) {
            add_x -= 26;
        } else if (this->_player.getPos().x + add_x == 2) {
            add_x += 26;
        }
        this->_player.setPos(ANAL::Vector2{this->_player.getPos().x + add_x, this->_player.getPos().y + add_y});
        add_x = 0;
        add_y = 0;
        return;
    }
    this->_player.setPos(ANAL::Vector2{this->_player.getPos().x + add_x, this->_player.getPos().y + add_y});
}

void arcade::games::Pacman::compute(ANAL::IArcade &arcade)
{
    if (this->_playername.empty())
        this->_playername = arcade.getPlayerName();
    if (this->_bestScore == -1)
        this->_bestScore = arcade.getPlayerHighscore(this->_playername);
    if (this->_player.getScore() > this->_bestScore && this->_player.getState() == Player::DEAD) {
        this->_bestScore = this->_player.getScore();
        arcade.setPlayerHighscore(this->_bestScore);
    }
    if (this->_player.getState() == Player::DEAD)
    {
        if (this->_player.getScore() > this->_bestScore)
        {
            this->_bestScore = this->_player.getScore();
            arcade.setPlayerHighscore(this->_bestScore);
        }
        return;
    }

    static int frame = 0;
    if (this->_ghostsTime > 0)
        _ghostsTime--;
    for (Ghost &e : this->_ghosts)
    {
        if (e.getState() == Ghost::DEAD)
        {
            if (e.getPos().x == e.getOrgPos().x && e.getPos().y == e.getOrgPos().y)
                e.tickDead();
            e.setPos({e.getOrgPos().x, e.getOrgPos().y});
        }
    }
    if (this->_player.getState() == Player::HIGH)
    {
        this->_player.tickHigh();
        for (Ghost &g : this->_ghosts)
            if (g.getState() != Ghost::DEAD)
                g.setState(Ghost::SCARED);
    }
    else
    {
        for (Ghost &g : this->_ghosts)
            if (g.getState() != Ghost::DEAD)
                g.setState(Ghost::NORMAL);
    }
    for (Ghost &e : this->_ghosts)
    {
        if (e.getPos().x == this->_player.getPos().x && e.getPos().y == this->_player.getPos().y)
        {
            if (this->_player.getState() == Player::HIGH)
            {
                e.setState(Ghost::DEAD);
                e.tickReset();
                this->_player.setScore(this->_player.getScore() + 300);
            }
            if (this->_player.getState() != Player::HIGH && e.getState() != Ghost::DEAD)
                this->_player.setState(Player::DEAD);
        }
    }
    if (frame++ < 2)
        return;
    frame = 0;
    if (this->_ghostsTime > 0)
        return;

    std::random_device rd;
    std::mt19937 rng(rd());
    static std::vector<ANAL::Vector2<int>> last_pos(this->_ghosts.size(), {0, 0});
    for (std::size_t i = 0; i < this->_ghosts.size(); ++i)
    {
        if (Ghost &g = this->_ghosts[i]; g.getState() != Ghost::DEAD)
        {
            ANAL::Vector2 pos = g.getPos();
            if (!g.getPassedGate())
            {
                if (this->_currentMap[pos.y + 1][pos.x - 1] == '_')
                {
                    g.setPassedGate(true);
                }
                else
                {
                    pos.y -= 1;
                    last_pos[i] = g.getPos();
                    g.setPos(pos);
                    continue;
                }
            }
            std::vector<ANAL::Vector2<int>> valid_moves;
            if (this->_currentMap[pos.y][pos.x - 1 - 1] != '#' && this->_currentMap[pos.y][pos.x - 1 - 1] != '_'
                && this->_currentMap[pos.y][pos.x - 1 - 1] != '!')
                valid_moves.emplace_back(pos.x - 1, pos.y);
            if (this->_currentMap[pos.y][pos.x + 1 - 1] != '#' && this->_currentMap[pos.y][pos.x + 1 - 1] != '_'
                && this->_currentMap[pos.y][pos.x + 1 - 1] != '!')
                valid_moves.emplace_back(pos.x + 1, pos.y);
            if (this->_currentMap[pos.y - 1][pos.x - 1] != '#' && this->_currentMap[pos.y - 1][pos.x - 1] != '_'
                && this->_currentMap[pos.y - 1][pos.x - 1] != '!')
                valid_moves.emplace_back(pos.x, pos.y - 1);
            if (this->_currentMap[pos.y + 1][pos.x - 1] != '#' && this->_currentMap[pos.y + 1][pos.x - 1] != '_'
                && this->_currentMap[pos.y + 1][pos.x - 1] != '!')
                valid_moves.emplace_back(pos.x, pos.y + 1);
            ANAL::Vector2<int> prev = last_pos[i];
            valid_moves.erase(
                std::remove_if(valid_moves.begin(), valid_moves.end(),
                    [&](const ANAL::Vector2<int>& v) {
                        return v.x == prev.x && v.y == prev.y;
                    }),
                valid_moves.end()
            );
            if (!valid_moves.empty())
            {
                std::shuffle(valid_moves.begin(), valid_moves.end(), rng);
                const auto p = valid_moves.front();
                if (p.x > g.getPos().x)
                    g.setLook(Ghost::RIGHT);
                else
                    g.setLook(Ghost::LEFT);
                last_pos[i] = g.getPos();
                g.setPos(p);
            }
        }
    }
}

void arcade::games::Pacman::render(ANAL::IRenderer &renderer, const ANAL::IArcade &arcade)
{
    renderer.clear();
    renderer.setWindowTitle("Pacman");
    for (int i = 0; i < 32; i++)
    {
        for (int j = 0; j < 29; j++)
        {
            auto const map_e = arcade.newEntity();
            auto const map_a = arcade.newAsset();
            std::string tile = "./assets/Pacman/textures/";
            switch (this->_currentMap[i][j])
            {
                case '#':
                    tile += "wall.png";
                    break;
                case '_':
                    tile += "gate.png";
                    break;
                case '.':
                    tile += "pacgum.png";
                    break;
                case 'o':
                    tile += "spacgum.png";
                    break;
                default:
                    tile += "void.png";
            }
            map_a->setTexturePath(tile);
            map_a->setAlternateRender(this->_currentMap[i][j]);
            map_e->setPos(ANAL::Vector2(j + 1, i));
            map_e->setAsset(*map_a);
            renderer.drawEntity(*map_e);
        }
    }
    renderer.drawText("Player: " + this->_playername, ANAL::Vector2(2, 0));
    renderer.drawText("Score: " + std::to_string(this->_player.getScore()), ANAL::Vector2(2, 1));
    renderer.drawText("Best: " + std::to_string(this->_bestScore), ANAL::Vector2(20, 1));
    auto const pacman_e = arcade.newEntity();
    auto const pacman_a = arcade.newAsset();
    std::string pass = "./assets/Pacman/textures/pacman";
    if (this->_player.getState() == Player::HIGH)
        pass += "_high";
    if (this->_player.getLook() == Player::LEFT)
        pass += "_inv";
    pacman_a->setTexturePath(pass + ".png");
    pacman_a->setAlternateRender('@');
    pacman_e->setPos(this->_player.getPos());
    pacman_e->setAsset(*pacman_a);
    renderer.drawEntity(*pacman_e);

    for (Ghost &g : this->_ghosts)
    {
        auto const ghost_e = arcade.newEntity();
        auto const ghost_a = arcade.newAsset();
        std::string path = "./assets/Pacman/textures/ghost_";
        if (g.getState() == Ghost::DEAD)
            path += "eyes";
        else if (g.getState() == Ghost::SCARED)
            path += "scared";
        else
            path += g.getColor();
        if (g.getLook() == Ghost::LEFT && g.getState() != Ghost::SCARED)
            path += "_inv";
        ghost_a->setTexturePath(path + ".png");
        ghost_a->setAlternateRender('$');
        ghost_e->setPos(g.getPos());
        ghost_e->setAsset(*ghost_a);
        renderer.drawEntity(*ghost_e);
    }
    static int frame = 0;
    frame++;
    if (this->_player.getState() == Player::DEAD)
    {
        if (frame / 20 % 2 == 0)
        {
            renderer.drawText(" Game Over", ANAL::Vector2(13, 13));
            renderer.drawText("Player: " + this->_playername, ANAL::Vector2(13, 14));
            renderer.drawText("Score: " + std::to_string(this->_player.getScore()), ANAL::Vector2(13, 15));
            renderer.drawText("Best: " + std::to_string(this->_bestScore), ANAL::Vector2(13, 16));
            renderer.drawText("Press R to restart", ANAL::Vector2(12, 17));
        }
    }
    if (frame >= 6000)
        frame = 0;
    renderer.render();
}

extern "C" std::unique_ptr<ANAL::IGame> uwu_entrypoint_game(void) { return std::make_unique<arcade::games::Pacman>(); }

ANAL::ModuleVersion uwu_get_module_version() { return ANAL::ModuleVersion::V1_1_0; }

ANAL::ModuleType uwu_get_module_type() { return ANAL::ModuleType::GAME; }
