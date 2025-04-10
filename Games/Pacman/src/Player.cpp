/*
** EPITECH PROJECT, 2025
** player
** File description:
** uwu
*/

#include "Pacman.hpp"

arcade::games::Player::Player()
{
    this->m_score = 0;
    this->m_state = NORMAL;
    this->m_look = RIGHT;
    this->m_tick_to_normal = 0;
}

[[nodiscard]] int arcade::games::Player::getScore() const { return this->m_score; }

void arcade::games::Player::setScore(const int Score) { this->m_score = Score; }

[[nodiscard]] ANAL::Vector2<int> arcade::games::Player::getPos() const { return this->m_player_pos; }

void arcade::games::Player::setPos(const ANAL::Vector2<int> v) { this->m_player_pos = v; }

[[nodiscard]] arcade::games::Player::STATE arcade::games::Player::getState() const { return this->m_state; }

void arcade::games::Player::setState(const STATE s) { this->m_state = s; }

void arcade::games::Player::tickHigh()
{
    if (this->m_tick_to_normal == 0)
    {
        this->setState(Player::NORMAL);
        return;
    }
    this->m_tick_to_normal--;
}

void arcade::games::Player::tickReset() { this->m_tick_to_normal = 100; }

[[nodiscard]] arcade::games::Player::LOOK arcade::games::Player::getLook() const { return this->m_look; }

void arcade::games::Player::setLook(const LOOK l) { this->m_look = l; }
