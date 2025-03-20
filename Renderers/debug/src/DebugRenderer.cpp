/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** DebugRenderer.cpp
*/

#include <iostream>

#include "DebugRenderer.hpp"

void DebugRenderer::drawSprite(const anal::ISprite& sprite)
{
    std::cout << "Should draw sprite" << std::endl;
}

void DebugRenderer::drawText(const std::string&, anal::Vector2<int>)
{
    std::cout << "Should draw text" << std::endl;
}

void DebugRenderer::setWindowTitle(const std::string& title)
{
    std::cout << "Should set window title to " << title << std::endl;
}

void DebugRenderer::render()
{
    std::cout << "Should render" << std::endl;
}

std::vector<anal::Event>& DebugRenderer::getEvents()
{
    return _events;
}

void DebugRenderer::clear()
{
    std::cout << "Should clear" << std::endl;
}

std::unique_ptr<anal::IRenderer> uwu_entrypoint_renderer()
    { return std::make_unique<DebugRenderer>(); }

std::unique_ptr<anal::IModule> uwu_entrypoint_module()
    { return std::make_unique<DebugRenderer>(); }
