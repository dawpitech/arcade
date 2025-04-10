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
#include "menu/MainMenu.hpp"
#include "utils/ModuleLoader.hpp"
#include "utils/SafeDirectoryLister.hpp"
#include "utils/ScoreStorage.hpp"

void Arcade::printHelp()
{
    std::cout << "USAGE: ./arcade <renderer.so>" << std::endl;
}

void Arcade::launch()
{
    if (this->_game == nullptr || this->_renderer == nullptr)
        throw std::exception();

    while (this->run) {
        const auto now = std::chrono::system_clock::now();
        const auto needed = now + std::chrono::operator ""ms(33);

	    auto events = this->_renderer->getEvents();
        this->handleHotKeys(dynamic_cast<MainMenu*>(this->_game.get()) != nullptr, events);
        this->_game->processEvents(events);
        this->_game->compute(*this);
        this->_game->render(*this->_renderer, *this);

        std::this_thread::sleep_until(needed);
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
}

void Arcade::handleHotKeys(const bool bypass, const std::vector<ANAL::Event>& events)
{
    for (const auto &[type, keyEvent, mouseEvent, closeEvent] : events)
    {
        if (type == ANAL::EventType::CLOSE)
            this->run = false;
        if (bypass)
            continue;
        if (type == ANAL::EventType::KEYBOARD && keyEvent.value().key == ANAL::Keys::KEY_N && keyEvent.value().state == ANAL::State::PRESSED) {
            this->nextGame();
            return;
        }
        if (type == ANAL::EventType::KEYBOARD && keyEvent.value().key == ANAL::Keys::KEY_B && keyEvent.value().state == ANAL::State::PRESSED) {
            this->nextRenderer();
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

const std::vector<std::string>& Arcade::getGamesList() const
{
    return this->_games;
}

const std::vector<std::string> &Arcade::getRenderersList() const
{
    return this->_renderers;
}

void Arcade::launchGame(const int idx)
{
    this->_game_idx = idx;
    this->nextGame();
}

void Arcade::nextGame()
{
    auto new_handle = SafeDL::open("./lib/" + this->_games.at(this->_game_idx), RTLD_LAZY);
    this->_game_idx = (this->_game_idx + 1) % this->_games.size();
    this->_game = ModuleLoader::loadGame(new_handle);
    this->_game_so_handle.swap(new_handle);
}

void Arcade::setRenderer(const int idx)
{
    this->_renderer_idx = idx;
    this->nextRenderer();
}

void Arcade::nextRenderer()
{
    auto new_handle = SafeDL::open("./lib/" + this->_renderers.at(this->_renderer_idx), RTLD_LAZY);
    this->_renderer_idx = (this->_renderer_idx + 1) % this->_renderers.size();
    this->_renderer.reset();
    this->_renderer = ModuleLoader::loadRenderer(new_handle);
    this->_renderer_so_handle.reset();
    this->_renderer_so_handle = std::move(new_handle);
}

const std::string &Arcade::getPlayerName() const
{
    return this->_playerName;
}

void Arcade::setPlayerHighscore(const int score)
{
    if (this->_playerName == "????")
        return;
    SaveFile::saveScore(this->_games.at(this->_game_idx), this->getPlayerName(), score);
}

int Arcade::getPlayerHighscore(const std::string &playerName) const
{
    if (playerName == "????")
        return 0;
    return SaveFile::loadScore(this->_games.at(this->_game_idx), this->getPlayerName());
}

void Arcade::setPlayername(const std::string &playername)
{
    this->_playerName = playername;
}
