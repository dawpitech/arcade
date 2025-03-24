/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** DebugRenderer.cpp
*/

#include <iostream>

#include "DebugRenderer.hpp"

void DebugRenderer::drawSprite(const ANAL::ISprite& sprite)
{
    std::cout << "Should draw sprite" << std::endl;
}

void DebugRenderer::drawText(const std::string&, ANAL::Vector2<int>)
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

std::vector<ANAL::Event>& DebugRenderer::getEvents()
{
    return _events;
}

void DebugRenderer::clear()
{
    std::cout << "Should clear" << std::endl;
}

ANAL::ModuleVersion uwu_get_module_version()
    { return ANAL::ModuleVersion::V1_1_0; }

ANAL::ModuleType uwu_get_module_type()
    { return ANAL::ModuleType::RENDERER; }

std::unique_ptr<ANAL::IRenderer> uwu_entrypoint_renderer()
    { return std::make_unique<DebugRenderer>(); }
