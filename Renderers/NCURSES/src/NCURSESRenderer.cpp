/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** NCURSESRenderer.cpp
*/

#include <csignal>
#include <iostream>
#include <ncurses.h>

#include "NCURSESRenderer.hpp"
#include "ANAL/IModule.hpp"

namespace
{
    volatile std::sig_atomic_t signal_received;
}

void sigint_handler(const int signal)
{
    signal_received = signal;
}

arcade::renderers::NCursesRenderer::NCursesRenderer() :
    _window(nullptr), _events({}), _screen(newterm(nullptr, stdout, stdin))
{
    std::signal(SIGINT, sigint_handler);
    keypad(_window, TRUE);
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

arcade::renderers::NCursesRenderer::~NCursesRenderer()
{
    std::signal(SIGINT, SIG_DFL);
    endwin();
    delwin(this->_window);
    set_term(this->_screen);
    std::cout.rdbuf(this->_backupbuffer);
}

void arcade::renderers::NCursesRenderer::drawEntity(const ANAL::IEntity &entity)
{
    const char entityChar = entity.getAsset().getAlternateRender();

    mvaddch(entity.getPos().y, entity.getPos().x, entityChar);
}

void arcade::renderers::NCursesRenderer::drawText(const std::string &str, const ANAL::Vector2<int> pos)
{
    mvwaddstr(this->_window, pos.y, pos.x, str.c_str());
}

void arcade::renderers::NCursesRenderer::setWindowTitle(const std::string &title) {}

void arcade::renderers::NCursesRenderer::render() { wrefresh(this->_window); }

void arcade::renderers::NCursesRenderer::clear()
{
    wclear(this->_window);
    wrefresh(this->_window);
}

std::vector<ANAL::Event> &arcade::renderers::NCursesRenderer::getEvents()
{
    static std::vector<ANAL::KeyEvent> pressedKeys;
    this->_events.clear();

    if (signal_received == 2) {
        constexpr ANAL::Event ev = {
            .type = ANAL::EventType::CLOSE,
        };

        this->_events.push_back(ev);
        return this->_events;
    }

    for (int chr = wgetch(stdscr); chr != ERR; chr = wgetch(stdscr)) {
        ANAL::Event ev;

        if (chr == KEY_MOUSE) {
            MEVENT mouseEvent;
            ev.type = ANAL::EventType::MOUSE;
            ev.mouseEvent = {
                .coords = ANAL::Vector2(mouseEvent.x / 16, mouseEvent.y / 16),
            };

            if (getmouse(&mouseEvent) != OK)
                throw Exception();

            for (const auto &[mask, key] : MOUSEBINDS_LIST) {
                if (!(mouseEvent.bstate & mask))
                    continue;
                ev.mouseEvent.value().key = key;
                ev.mouseEvent.value().state =
                    mask & (BUTTON1_PRESSED | BUTTON2_PRESSED | BUTTON3_PRESSED)
                        ? ANAL::State::PRESSED
                        : ANAL::State::RELEASED;
                break;
            }

            this->_events.insert(this->_events.end(), ev);
            continue;
        }

        try
        {
            const ANAL::Keys key = KEYBINDS_MAP.at(chr);
            ev.keyEvent = {
                .key = key,
                .state = ANAL::State::PRESSED,
            };
            ev.type = ANAL::EventType::KEYBOARD;
            ANAL::Event ev_invert_cpy = ev;
            ev_invert_cpy.keyEvent->state = ANAL::State::RELEASED;
            this->_events.insert(this->_events.end(), ev);
            this->_events.insert(this->_events.end(), ev_invert_cpy);
        } catch (std::out_of_range&) {}
    }

    return this->_events;
}

ANAL::ModuleVersion uwu_get_module_version() { return ANAL::ModuleVersion::V1_1_0; }

ANAL::ModuleType uwu_get_module_type() { return ANAL::ModuleType::RENDERER; }

extern "C" std::unique_ptr<ANAL::IRenderer> uwu_entrypoint_renderer()
{
    return std::make_unique<arcade::renderers::NCursesRenderer>();
}
