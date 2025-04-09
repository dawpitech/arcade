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

arcade::renderers::SFMLRenderer::SFMLRenderer()
    : _window(sf::VideoMode(WINDOW_SIZE * SCALE_FACTOR, WINDOW_SIZE * SCALE_FACTOR), "Arcade", sf::Style::Default | sf::Style::Titlebar)
    , _events({})
{
}

arcade::renderers::SFMLRenderer::~SFMLRenderer()
{
    this->_window.close();
}

void arcade::renderers::SFMLRenderer::drawEntity(const ANAL::IEntity& entity)
{
    sf::Texture texture;
    if (!texture.loadFromFile(entity.getAsset().getTexturePath()))
        throw Exception();
    sf::Sprite sfSprite(texture);
    sfSprite.setPosition(static_cast<float>(entity.getPos().x * SCALE_FACTOR),
			 static_cast<float>(entity.getPos().y * SCALE_FACTOR));
    this->_window.draw(sfSprite);
}

void arcade::renderers::SFMLRenderer::drawText(const std::string& str,
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

void arcade::renderers::SFMLRenderer::setWindowTitle(const std::string& title)
{
    this->_window.setTitle(title);
}

void arcade::renderers::SFMLRenderer::render()
{
    this->_window.display();
}

void arcade::renderers::SFMLRenderer::clear()
{
    this->_window.clear();
}

std::vector<ANAL::Event>& arcade::renderers::SFMLRenderer::getEvents()
{
    sf::Event event{};
    this->_events.clear();
    while (_window.pollEvent(event)) {
        ANAL::Event ev;

        switch (event.type)
        {
            case sf::Event::Closed:
                ev.type = ANAL::EventType::CLOSE;
                this->_events.insert(this->_events.end(), ev);
                break;
            case sf::Event::KeyReleased:
            case sf::Event::KeyPressed:
                try {
                    ev.keyEvent = {
                        .key = KEYBINDS_MAP.at(event.key.code),
                        .state = event.type == sf::Event::KeyPressed ? ANAL::State::PRESSED : ANAL::State::RELEASED,
                    };
                    ev.type = ANAL::EventType::KEYBOARD;
                    this->_events.insert(this->_events.end(), ev);
                } catch (std::out_of_range&) {}
                break;
            case sf::Event::MouseButtonPressed:
                case sf::Event::MouseButtonReleased:
                try {
                    ev.mouseEvent = {
                        .coords = ANAL::Vector2(event.mouseButton.x / 16, event.mouseButton.y / 16),
                        .key = MOUSEBINDS_MAP.at(event.mouseButton.button),
                        .state = event.type == sf::Event::MouseButtonPressed ? ANAL::State::PRESSED : ANAL::State::RELEASED,
                    };
                    ev.type = ANAL::EventType::MOUSE;
                    this->_events.insert(this->_events.end(), ev);
                } catch (std::out_of_range&) {}
                break;
            default:
                break;
        }
    }
    return this->_events;
}

ANAL::ModuleVersion uwu_get_module_version()
    { return ANAL::ModuleVersion::V1_1_0; }

ANAL::ModuleType uwu_get_module_type()
    { return ANAL::ModuleType::RENDERER; }

extern "C" std::unique_ptr<ANAL::IRenderer> uwu_entrypoint_renderer()
    { return std::make_unique<arcade::renderers::SFMLRenderer>(); }
