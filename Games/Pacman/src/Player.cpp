/*
** EPITECH PROJECT, 2025
** player
** File description:
** uwu
*/

#include "Pacman.hpp"

Player::Player() {
    this->m_score = 0;
    this->m_state = NORMAL;
    this->m_look = RIGHT;
    this->m_tick_to_normal = 0;
}

[[nodiscard]] int Player::getScore() const {
    return this->m_score;
}

void Player::setScore(int Score) {
    this->m_score = Score;
}

[[nodiscard]] ANAL::Vector2<int> Player::getPos() const {
    return this->m_player_pos;
}

void Player::setPos(ANAL::Vector2<int> v) {
    this->m_player_pos = v;
}

[[nodiscard]] Player::STATE Player::getState() const {
    return this->m_state;
}

void Player::setState(Player::STATE s) {
    this->m_state = s;
}

void Player::tickHigh() {
    if (this->m_tick_to_normal == 0) {
	this->setState(Player::NORMAL);
	return;
    }
    this->m_tick_to_normal--;
}

void Player::tickReset() {
    this->m_tick_to_normal = 100;
}

[[nodiscard]] Player::LOOK Player::getLook() const {
    return this->m_look;
}

void Player::setLook(Player::LOOK l) {
    this->m_look = l;
}
