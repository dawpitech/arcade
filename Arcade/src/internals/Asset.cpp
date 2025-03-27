/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Asset.cpp
*/

#include <string>

#include "Asset.hpp"

char Asset::getAlternateRender() const
{
    return this->_alternateRender;
}

const std::string& Asset::getTexturePath() const
{
    return this->_texturePath;
}

void Asset::setAlternateRender(const char chr)
{
    this->_alternateRender = chr;
}

void Asset::setTexturePath(const std::string& path)
{
    this->_texturePath = path;
}
