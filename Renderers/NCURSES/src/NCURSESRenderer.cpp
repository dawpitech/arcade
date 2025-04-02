/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** NCURSESRenderer.cpp
*/

#include <iostream>
#include <ncurses.h>

#include "NCURSESRenderer.hpp"
#include "ANAL/IModule.hpp"

arcade::NCursesRenderer::NCursesRenderer()
    : _window(nullptr)
    , _events({})
{
    initscr();
    raw();
    noecho();
    cbreak();
    curs_set(0);
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    this->_window = stdscr;

    this->_backupbuffer = std::cout.rdbuf();
    std::cout.rdbuf(this->_nullstream.rdbuf()); 
}

arcade::NCursesRenderer::~NCursesRenderer()
{
    endwin();
    delwin(this->_window);
    std::cout.rdbuf(this->_backupbuffer);
}

void arcade::NCursesRenderer::drawEntity(const ANAL::IEntity& entity)
{
    const char entityChar = entity.getAsset().getAlternateRender();

    mvaddch(entity.getPos().y, entity.getPos().x, entityChar);
}

void arcade::NCursesRenderer::drawText(const std::string& str, const ANAL::Vector2<int> pos)
{
    mvwaddstr(this->_window, pos.y, pos.x, str.c_str());
}

void arcade::NCursesRenderer::setWindowTitle(const std::string& title)
{
}

void arcade::NCursesRenderer::render()
{
    wrefresh(this->_window);
}

void arcade::NCursesRenderer::clear()
{
    wclear(this->_window);
    wrefresh(this->_window);
}

std::vector<ANAL::Event>& arcade::NCursesRenderer::getEvents()
{
    static std::vector<ANAL::KeyEvent> pressedKeys;
    this->_events.clear();

    for (auto it = pressedKeys.begin(); it != pressedKeys.end();) {
	ANAL::Event ev;
	ev.type = ANAL::EventType::KEYBOARD;
	ANAL::KeyEvent keyEvent = *it;
	keyEvent.state = ANAL::State::RELEASED;

	ev.keyEvent = keyEvent;
	this->_events.insert(this->_events.end(), ev);
	it = pressedKeys.erase(it);
    }
    const int ch = getch();
    if (ch != ERR) {
        ANAL::Event ev;
        if (ch == 'q') {
            ev.type = ANAL::EventType::CLOSE;
            this->_events.insert(this->_events.end(), ev);
        } else {
            ev.type = ANAL::EventType::KEYBOARD;
            ANAL::KeyEvent keyEvent;
            keyEvent.state = ANAL::State::PRESSED;
            
            switch (ch) {
                case KEY_UP:
                    keyEvent.key = ANAL::Keys::ARROW_UP;
                    break;
                case KEY_DOWN:
                    keyEvent.key = ANAL::Keys::ARROW_DOWN;
                    break;
                case KEY_LEFT:
                    keyEvent.key = ANAL::Keys::ARROW_LEFT;
                    break;
                case KEY_RIGHT:
                    keyEvent.key = ANAL::Keys::ARROW_RIGHT;
                    break;
                case 'r':
                    keyEvent.key = ANAL::Keys::KEY_R;
                    break;
                default:
                    return this->_events;
            }
            
            ev.keyEvent = keyEvent;
            this->_events.insert(this->_events.end(), ev);
            pressedKeys.push_back(keyEvent);
        }
    } 
    return this->_events;
}

ANAL::ModuleVersion uwu_get_module_version()
    { return ANAL::ModuleVersion::V1_1_0; }

ANAL::ModuleType uwu_get_module_type()
    { return ANAL::ModuleType::RENDERER; }

extern "C" std::unique_ptr<ANAL::IRenderer> uwu_entrypoint_renderer()
    { return std::make_unique<arcade::NCursesRenderer>(); }
