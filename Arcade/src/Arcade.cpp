/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** Arcade.cpp
*/

#include <iostream>
#include <thread>

#include "Arcade.hpp"
#include "ANAL/Events.hpp"
#include "internals/Asset.hpp"
#include "internals/Entity.hpp"

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
        for (const auto event : this->_renderer->getEvents())
	    if (event.type == ANAL::EventType::CLOSE)
                this->run = false;
        this->_game->processEvents(this->_renderer->getEvents());

        // TODO: add proper fps clamping using hardware clock
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));

        this->_game->compute();
        this->_game->render(*this->_renderer, *this);

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

std::unique_ptr<ANAL::IAsset> Arcade::newAsset() const
{
    return std::make_unique<Asset>();
}

std::unique_ptr<ANAL::IEntity> Arcade::newEntity() const
{
    return std::make_unique<Entity>();
}
