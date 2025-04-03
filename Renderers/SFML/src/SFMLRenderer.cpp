/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** SFMLRenderer.cpp
*/

#include <iostream>
#include <SFML/Graphics.hpp>

#include "SFMLRenderer.hpp"
#include "ANAL/Events.hpp"
#include "ANAL/IModule.hpp"

arcade::SFMLRenderer::SFMLRenderer()
    : _window(sf::VideoMode(WINDOW_SIZE * SCALE_FACTOR, WINDOW_SIZE * SCALE_FACTOR), "Arcade")
    , _events({})
{
    std::cout << "SFML Init" << std::endl;
}

arcade::SFMLRenderer::~SFMLRenderer()
{
    this->_window.close();
    std::cout << "SFML Destroyed" << std::endl;
}

void arcade::SFMLRenderer::drawEntity(const ANAL::IEntity& entity)
{
    sf::Texture texture;
    if (!texture.loadFromFile(entity.getAsset().getTexturePath()))
        throw Exception();
    sf::Sprite sfSprite(texture);
    sfSprite.setPosition(static_cast<float>(entity.getPos().x * SCALE_FACTOR),
			 static_cast<float>(entity.getPos().y * SCALE_FACTOR));
    this->_window.draw(sfSprite);
}

void arcade::SFMLRenderer::drawText(const std::string& str,
    const ANAL::Vector2<int> pos)
{
    sf::Font font;
    if (!font.loadFromFile("./assets/fonts/Abordage-Regular.ttf"))
        throw Exception();
    sf::Text text(str, font, FONT_SIZE * SCALE_FACTOR);
    text.setPosition(static_cast<float>(pos.x) * SCALE_FACTOR, static_cast<float>(pos.y) * SCALE_FACTOR);
    text.setFillColor(sf::Color::White);
    this->_window.draw(text);
}

void arcade::SFMLRenderer::setWindowTitle(const std::string& title)
{
    this->_window.setTitle(title);
}

void arcade::SFMLRenderer::render()
{
    this->_window.display();
}

void arcade::SFMLRenderer::clear()
{
    this->_window.clear();
}

std::vector<ANAL::Event>& arcade::SFMLRenderer::getEvents()
{
    sf::Event event;
    this->_events.clear();
    while (_window.pollEvent(event)) {
        ANAL::Event ev;
        if (event.type == sf::Event::Closed) {
            ev.type = ANAL::EventType::CLOSE;
            this->_events.insert(this->_events.end(), ev);
        } else if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased) {
            ev.type = ANAL::EventType::KEYBOARD;
            ANAL::KeyEvent keyEvent;
            keyEvent.state = (event.type == sf::Event::KeyPressed) ? ANAL::State::PRESSED : ANAL::State::RELEASED;
            
            switch (event.key.code) {
                case sf::Keyboard::Up:
                    keyEvent.key = ANAL::Keys::ARROW_UP;
                    break;
                case sf::Keyboard::Down:
                    keyEvent.key = ANAL::Keys::ARROW_DOWN;
                    break;
                case sf::Keyboard::Left:
                    keyEvent.key = ANAL::Keys::ARROW_LEFT;
                    break;
                case sf::Keyboard::Right:
                    keyEvent.key = ANAL::Keys::ARROW_RIGHT;
                    break;
                case sf::Keyboard::R:
                    keyEvent.key = ANAL::Keys::KEY_R;
                    break;
                case sf::Keyboard::B:
                    keyEvent.key = ANAL::Keys::KEY_B;
                    break;
                case sf::Keyboard::N:
                    keyEvent.key = ANAL::Keys::KEY_N;
                    break;
                default:
                    continue;
            }
            ev.keyEvent = keyEvent;
            this->_events.insert(this->_events.end(), ev);
        }
    }
    return this->_events;
}

ANAL::ModuleVersion uwu_get_module_version()
    { return ANAL::ModuleVersion::V1_1_0; }

ANAL::ModuleType uwu_get_module_type()
    { return ANAL::ModuleType::RENDERER; }

extern "C" std::unique_ptr<ANAL::IRenderer> uwu_entrypoint_renderer()
    { return std::make_unique<arcade::SFMLRenderer>(); }
