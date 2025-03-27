/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Entity.cpp
*/

#include "Entity.hpp"

const ANAL::IAsset& Entity::getAsset() const
{
    return *this->_asset;
}

const ANAL::Vector2<int>& Entity::getPos() const
{
    return this->_pos;
}

void Entity::setPos(const ANAL::Vector2<int>& pos)
{
    this->_pos = pos;
}

void Entity::setAsset(const ANAL::IAsset& asset)
{
    this->_asset = std::make_unique<Asset>(dynamic_cast<const Asset&>(asset));
}
