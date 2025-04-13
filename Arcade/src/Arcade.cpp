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

        auto& real_events = this->_renderer->getEvents();
	    auto events = real_events;
        this->handleHotKeys(dynamic_cast<MainMenu*>(this->_game.get()) != nullptr, events);
        this->_game->processEvents(events);
        this->_game->compute(*this);
        this->_game->render(*this->_renderer, *this);

        real_events.clear();
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
        if (type == ANAL::EventType::KEYBOARD && keyEvent->key == ANAL::Keys::KEY_N && keyEvent->state == ANAL::State::PRESSED) {
            this->nextGame();
            return;
        }
        if (type == ANAL::EventType::KEYBOARD && keyEvent->key == ANAL::Keys::KEY_B && keyEvent->state == ANAL::State::PRESSED) {
            this->nextRenderer();
            return;
        }
        if (type == ANAL::EventType::KEYBOARD && keyEvent->key == ANAL::Keys::KEY_R && keyEvent->state == ANAL::State::PRESSED) {
            this->restartGame();
            return;
        }
        if (type == ANAL::EventType::KEYBOARD && keyEvent->key == ANAL::Keys::KEY_M && keyEvent->state == ANAL::State::PRESSED) {
            this->loadMenu();
            return;
        }
        if (type == ANAL::EventType::KEYBOARD && keyEvent->key == ANAL::Keys::KEY_Q && keyEvent->state == ANAL::State::PRESSED) {
            this->run = false;
            return;
        }
    }
}

void Arcade::restartGame()
{
    this->launchGame(static_cast<int>(this->_game_idx));
}

void Arcade::loadMenu()
{
    this->_game_idx = 0;
    this->_game.reset();
    this->_game_so_handle.reset();
    this->_game = std::make_unique<MainMenu>();
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
    this->_lastGame = this->_games.at(this->_game_idx);
    this->_game_idx = idx;
    auto new_handle = SafeDL::open("./lib/" + this->_games.at(this->_game_idx), RTLD_LAZY);
    this->_game.reset();
    this->_game = ModuleLoader::loadGame(new_handle);
    this->_game_so_handle.reset();
    this->_game_so_handle.swap(new_handle);
    this->_game_idx = idx;
}

void Arcade::nextGame()
{
    this->_game_idx = (this->_game_idx + 1) % this->_games.size();
    this->launchGame(static_cast<int>(this->_game_idx));
}

void Arcade::setRenderer(const int idx)
{
    this->_renderer_idx = idx;
    auto new_handle = SafeDL::open("./lib/" + this->_renderers.at(this->_renderer_idx), RTLD_LAZY);
    this->_renderer.reset();
    this->_renderer = ModuleLoader::loadRenderer(new_handle);
    this->_renderer_so_handle.reset();
    this->_renderer_so_handle = std::move(new_handle);
}

void Arcade::nextRenderer()
{
    this->_renderer_idx = (this->_renderer_idx + 1) % this->_renderers.size();
    this->setRenderer(static_cast<int>(this->_renderer_idx));
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

const std::string &Arcade::getLastGameName() const
{
    return this->_lastGame;
}
