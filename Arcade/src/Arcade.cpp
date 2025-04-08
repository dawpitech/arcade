/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** Arcade.cpp
*/

#include <iostream>
#include <thread>

#include "ANAL/Events.hpp"
#include "Arcade.hpp"
#include "internals/Asset.hpp"
#include "internals/Entity.hpp"
#include "utils/ModuleLoader.hpp"
#include "utils/SafeDirectoryLister.hpp"

void Arcade::printHelp()
{
    std::cout << "USAGE: ./arcade <renderer.so>" << std::endl;
}

void Arcade::launch()
{
    if (this->_game == nullptr || this->_renderer == nullptr)
        throw std::exception();

    while (this->run) {
	    auto events = this->_renderer->getEvents();
        this->handleHotKeys(events);
        this->_game->processEvents(events);

        // TODO: add proper fps clamping using hardware clock
        std::this_thread::sleep_for(std::chrono::milliseconds(20));

        this->_game->compute();
        this->_game->render(*this->_renderer, *this);
    }
}

bool Arcade::str_ends_with(const std::string &str, const std::string &suffix)
{
    return str.size() >= suffix.size() &&
        str.compare(str.size()-suffix.size(), suffix.size(), suffix) == 0;
}

void Arcade::scanForModules()
{
    try
    {
        const SafeDirectoryLister dl("./lib", false);
        for (std::string path = dl.get();; path = dl.get()) {
            if (!str_ends_with(path, ".so"))
                continue;
            try
            {
                switch (const auto dll = SafeDL::open("./lib/" + path, RTLD_LAZY);
                    ModuleLoader::getModuleType(dll))
                {
                    case ANAL::ModuleType::GAME:
                        this->addToGameList(path);
                    break;
                    case ANAL::ModuleType::RENDERER:
                        this->addToRendererList(path);
                    default:
                        break;
                }
            } catch (std::exception&) {}
        }
    } catch (SafeDirectoryLister::NoMoreFileException&) {}
    //printf("Games: %lu\n", this->_games.size());
    //printf("Renderers: %lu\n", this->_renderers.size());
}

void Arcade::handleHotKeys(const std::vector<ANAL::Event>& events)
{
    for (const auto &[type, keyEvent, mouseEvent, closeEvent] : events)
    {
        if (type == ANAL::EventType::CLOSE)
            this->run = false;
        if (type == ANAL::EventType::KEYBOARD && keyEvent.value().key == ANAL::Keys::KEY_N && keyEvent.value().state == ANAL::State::PRESSED) {
            //printf("loading game id %lu\n", this->_game_idx);
            auto new_handle = SafeDL::open("./lib/" + this->_games.at(this->_game_idx), RTLD_LAZY);
            this->_game_idx = (this->_game_idx + 1) % this->_games.size();
            this->_game.reset();
            this->_game = ModuleLoader::loadGame(new_handle);
            this->_game_so_handle.reset();
            this->_game_so_handle.swap(new_handle);
            return;
        }
        if (type == ANAL::EventType::KEYBOARD && keyEvent.value().key == ANAL::Keys::KEY_B && keyEvent.value().state == ANAL::State::PRESSED) {
            //printf("loading renderer id %lu\n", this->_renderer_idx);
            auto new_handle = SafeDL::open("./lib/" + this->_renderers.at(this->_renderer_idx), RTLD_LAZY);
            this->_renderer_idx = (this->_renderer_idx + 1) % this->_renderers.size();
            this->_renderer.reset();
            this->_renderer = ModuleLoader::loadRenderer(new_handle);
            this->_renderer_so_handle.reset();
            this->_renderer_so_handle = std::move(new_handle);
            return;
        }
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

void Arcade::addToGameList(const std::string &str)
{
    this->_games.push_back(str);
}

void Arcade::addToRendererList(const std::string &str)
{
    this->_renderers.push_back(str);
}

std::unique_ptr<ANAL::IAsset> Arcade::newAsset() const
{
    return std::make_unique<Asset>();
}

std::unique_ptr<ANAL::IEntity> Arcade::newEntity() const
{
    return std::make_unique<Entity>();
}

const std::vector<std::string> &Arcade::getGamesList() const
{
    return this->_games;
}

void Arcade::launchGame(const int idx)
{
    this->_game_idx = idx;
    auto new_handle = SafeDL::open("./lib/" + this->_games.at(this->_game_idx), RTLD_LAZY);
    this->_game_idx = (this->_game_idx + 1) % this->_games.size();
    this->_game = ModuleLoader::loadGame(new_handle);
    this->_game_so_handle.swap(new_handle);
}
