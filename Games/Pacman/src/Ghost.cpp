/*
** EPITECH PROJECT, 2025
** Ghost
** File description:
** uwu
*/

#include "Pacman.hpp"

Ghost::Ghost(ANAL::Vector2<int> pos, const std::string &color) {
    this->m_state = NORMAL;
    this->m_look = RIGHT;
    this->m_passed_gate = false;
    this->m_tick_to_normal = 0;
    this->m_ghost_pos = pos;
    this->m_ghost_org_pos = pos;
    this->m_color = color;
}

[[nodiscard]] ANAL::Vector2<int> Ghost::getPos() const {
    return this->m_ghost_pos;
}

[[nodiscard]] ANAL::Vector2<int> Ghost::getOrgPos() const {
    return this->m_ghost_org_pos;
}

void Ghost::setPos(ANAL::Vector2<int> v) {
    this->m_ghost_pos = v;
}

[[nodiscard]] Ghost::STATE Ghost::getState() const {
    return this->m_state;
}

void Ghost::setState(Ghost::STATE s) {
    if (this->m_state == DEAD) {
	this->setPassedGate(false);
    }
    this->m_state = s;
}

void Ghost::tickDead() {
    if (this->m_tick_to_normal == 0) {
	this->setState(Ghost::NORMAL);
	return;
    }
    this->m_tick_to_normal--;
}

void Ghost::tickReset() {
    this->m_tick_to_normal = 300;
}

[[nodiscard]] Ghost::LOOK Ghost::getLook() const {
    return this->m_look;
}

void Ghost::setLook(Ghost::LOOK l) {
    this->m_look = l;
}

[[nodiscard]] std::string Ghost::getColor() const {
    return this->m_color;
}

void Ghost::setColor(std::string &col) {
    this->m_color = col;
}

[[nodiscard]] bool Ghost::getPassedGate() const {
    return this->m_passed_gate;
}

void Ghost::setPassedGate(const bool &p) {
    this->m_passed_gate = p;
}
