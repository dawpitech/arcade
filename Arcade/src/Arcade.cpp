/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** Arcade.cpp
*/

#include <iostream>

#include "Arcade.hpp"

#include <thread>

void Arcade::printHelp()
{
    std::cout << "USAGE: ./arcade </path/to/a/renderer.so>" << std::endl;
}

void Arcade::launch()
{
    if (this->_game == nullptr || this->_renderer == nullptr)
        throw std::exception();

    while (this->run)
    {
        this->_game->processEvents(std::vector<ANAL::Event>());
        this->_game->compute();
        this->_game->render(*this->_renderer);

        // TODO: add proper fps clamping using hardware clock
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        this->run = false;
    }
}

void Arcade::setGame(std::unique_ptr<ANAL::IGame>& game)
{
    this->_game = std::move(game);
}

void Arcade::setRenderer(std::unique_ptr<ANAL::IRenderer>& renderer)
{
    this->_renderer = std::move(renderer);
}
