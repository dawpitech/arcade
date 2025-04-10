/*
** EPITECH PROJECT, 2025
** Ghost
** File description:
** uwu
*/

#include "Pacman.hpp"

arcade::games::Ghost::Ghost(const ANAL::Vector2<int> pos, const std::string &color)
{
    this->m_state = NORMAL;
    this->m_look = RIGHT;
    this->m_passed_gate = false;
    this->m_tick_to_normal = 0;
    this->m_ghost_pos = pos;
    this->m_ghost_org_pos = pos;
    this->m_color = color;
}

[[nodiscard]] ANAL::Vector2<int> arcade::games::Ghost::getPos() const { return this->m_ghost_pos; }

[[nodiscard]] ANAL::Vector2<int> arcade::games::Ghost::getOrgPos() const { return this->m_ghost_org_pos; }

void arcade::games::Ghost::setPos(const ANAL::Vector2<int> v) { this->m_ghost_pos = v; }

[[nodiscard]] arcade::games::Ghost::STATE arcade::games::Ghost::getState() const { return this->m_state; }

void arcade::games::Ghost::setState(const STATE s)
{
    if (this->m_state == DEAD)
        this->setPassedGate(false);
    this->m_state = s;
}

void arcade::games::Ghost::tickDead()
{
    if (this->m_tick_to_normal == 0)
    {
        this->setState(NORMAL);
        return;
    }
    this->m_tick_to_normal--;
}

void arcade::games::Ghost::tickReset() { this->m_tick_to_normal = 300; }

[[nodiscard]] arcade::games::Ghost::LOOK arcade::games::Ghost::getLook() const { return this->m_look; }

void arcade::games::Ghost::setLook(const LOOK l) { this->m_look = l; }

[[nodiscard]] std::string arcade::games::Ghost::getColor() const { return this->m_color; }

void arcade::games::Ghost::setColor(const std::string &col) { this->m_color = col; }

[[nodiscard]] bool arcade::games::Ghost::getPassedGate() const { return this->m_passed_gate; }

void arcade::games::Ghost::setPassedGate(const bool &p) { this->m_passed_gate = p; }
