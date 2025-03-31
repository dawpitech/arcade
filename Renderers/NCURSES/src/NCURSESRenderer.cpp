/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** NCURSESRenderer.cpp
*/

#include <ncurses.h>
#include <iostream>
#include <cstdio>
#include <unistd.h>
#include <ANAL/IModule.hpp>
#include "NCURSESRenderer.hpp"

arcade::NCursesRenderer::NCursesRenderer()
    : _window(nullptr)
    , _events({})
{
    initscr();
    raw();
    noecho();
    cbreak();
    curs_set(0);
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
    char entityChar = entity.getAsset().getAlternateRender(); 

    mvaddch(entity.getPos().y, entity.getPos().x, entityChar);
}

void arcade::NCursesRenderer::drawText(const std::string& str, const ANAL::Vector2<int> pos)
{
    mvwprintw(this->_window, pos.y, pos.x, str.c_str());
}

void arcade::NCursesRenderer::setWindowTitle(const std::string& title)
{
}

void arcade::NCursesRenderer::render()
{
    refresh();
}

void arcade::NCursesRenderer::clear()
{
}

std::vector<ANAL::Event>& arcade::NCursesRenderer::getEvents()
{
    this->_events.clear();

    int ch = getch();
    if (ch == ERR)
        return this->_events;

    if (ch == 'q')
        this->_events.push_back(ANAL::Event::CLOSE);

    return this->_events;
}

ANAL::ModuleVersion uwu_get_module_version()
    { return ANAL::ModuleVersion::V1_1_0; }

ANAL::ModuleType uwu_get_module_type()
    { return ANAL::ModuleType::RENDERER; }

extern "C" std::unique_ptr<ANAL::IRenderer> uwu_entrypoint_renderer()
    { return std::make_unique<arcade::NCursesRenderer>(); }
