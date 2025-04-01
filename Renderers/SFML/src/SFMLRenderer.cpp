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
    : _window(sf::VideoMode(600, 600), "Arcade")
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
    sfSprite.setPosition(static_cast<float>(entity.getPos().x)*40,
        static_cast<float>(entity.getPos().y)*40);
    sfSprite.setScale(4, 4);
    this->_window.draw(sfSprite);
}

void arcade::SFMLRenderer::drawText(const std::string& str,
    const ANAL::Vector2<int> pos)
{
    sf::Font font;
    if (!font.loadFromFile("./assets/fonts/Abordage-Regular.ttf"))
        throw Exception();
    sf::Text text(str, font, 30);
    text.setPosition(static_cast<float>(pos.x)*40, static_cast<float>(pos.y)*40);
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
    sf::Event event{};
    while(_window.pollEvent(event))
    {
	ANAL::Event ev;
        if (event.type == sf::Event::Closed) {
	    ev.type = ANAL::EventType::CLOSE;
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
