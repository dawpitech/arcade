/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** Arcade.cpp
*/

#include "Minesweeper.hpp"
#include <string>
#include "ANAL/Events.hpp"
#include "ANAL/IModule.hpp"
#include "ANAL/Vector2.hpp"
#include <iostream>

void Minesweeper::Game::init()
{
    this->_board = Board();
    this->m_state = EMPTY_MAP;
    this->m_click = UNKNOWN;
    this->m_bestscore = -1;
    this->m_player_name = "";
    this->_flags = NUMBER_OF_BOMBS;
}

void Minesweeper::Game::restart()
{
    this->_board.clearMap();
    this->_coor = {0, 0};
    this->_flags = NUMBER_OF_BOMBS;
    this->_bombflagged = 0;
    this->_board.initializeMap();
}

Minesweeper::Game::Game()
{
    this->init();
}

void Minesweeper::Game::processEvents(std::vector<ANAL::Event> &ev)
{
    static bool _left = 0;
    static bool _right = 0;
    static ANAL::Vector2<int> _new_coor(0, 0);
    for (auto e : ev) {
        switch (e.type) {
            case ANAL::EventType::MOUSE: {
                auto mouse = e.mouseEvent.value().key;
                auto click_mouse = e.mouseEvent.value().state == ANAL::State::RELEASED;
                if (mouse == ANAL::MouseKeys::LEFT_CLICK) {
                    this->m_click = LEFT;
                    _new_coor = e.mouseEvent.value().coords;
                }
                if (mouse == ANAL::MouseKeys::RIGHT_CLICK) {
                    this->m_click = RIGHT;
                    _new_coor = e.mouseEvent.value().coords;
                }
                break;
            }
            default:
                break;
        }
    }
    for (auto e : ev)
    {
        switch (e.type)
        {
            case ANAL::EventType::KEYBOARD:
            {
                auto key = e.keyEvent.value().key;
                auto down = e.keyEvent.value().state == ANAL::State::RELEASED;
                if (key == ANAL::Keys::KEY_R)
                    this->m_state = RESTART;
                break;
            }
            default:
                break;
        }
    }
    if (this->getState() == HAS_RESTART || this->getState() == DEFEAT) {
        this->_coor = {0,0};
        this->m_click = UNKNOWN;
        if (this->getState() == HAS_RESTART)
            this->m_state = WORKS;
        if (this->getState() == DEFEAT)
            this->m_state = DEFEAT;
        return;
    }
    this->_coor = _new_coor;
    this->_coor.x = this->_coor.x - 1;
    this->_coor.y = this->_coor.y - 7;
    if ((this->_coor.x < 0 || this->_coor.y < 0) || (this->_coor.x > SIZE_ARRAY_CELL - 1 || this->_coor.y > SIZE_ARRAY_ROW - 1)) {
        this->m_click = UNKNOWN;
        return;
    }
}

void Minesweeper::Game::compute(ANAL::IArcade& arcade) {
    if (this->m_player_name == "")
	    this->m_player_name = arcade.getPlayerName();
    if (this->m_bestscore == -1)
	    this->m_bestscore = arcade.getPlayerHighscore(this->m_player_name);
    if (this->getState() == DEFEAT) {
        this->_board.mapVisible();
        this->_mapDisplay = this->_board.mapToDisplay();
        return;
    }
    if (this->getState() == RESTART) {
        this->restart();
        this->_fClick = true;
        this->m_state = HAS_RESTART;
        return;
    }
    if (this->m_click == UNKNOWN) {
        this->_mapDisplay = this->_board.mapToDisplay();
        return;
    }
    if (this->getClick() == LEFT && this->getState() == WORKS) {
        if (this->_board.isBomb(this->_coor) == true && this->_fClick == true) {
            this->restart();
            return;
        }
        this->_fClick = false;
        if (this->_board.isBomb(this->_coor) == true)
            this->m_state = DEFEAT;
        this->_board.toVisible(this->_coor.x, this->_coor.y);
    }
    if (this->getClick() == RIGHT && this->getState() == WORKS) {
        this->_fClick = false;
        if (this->_board.isVisible(this->_coor) == true)
            return;
        if (this->_board.isFlag(this->_coor) == false) {
            this->_board.toFlag(this->_coor.x, this->_coor.y);
            this->_flags -= 1;
            this->_bombflagged += this->bBF();
        }
    }
    if (this->_fClick == true && this->_board.bombDiscover() == true) {
        this->restart();
        return;
    }
    this->_mapDisplay = this->_board.mapToDisplay();
}

void Minesweeper::Game::render(ANAL::IRenderer &renderer, const ANAL::IArcade &arcade) {
    renderer.clear();
    renderer.setWindowTitle("Minesweeper");
    if (this->getState() == EMPTY_MAP) {
        if (this->_mapDisplay.empty()) {
            return;
        }
        this->m_state = WORKS;
    }
    for (int row = 0; row < SIZE_ARRAY_ROW; row++)
    {
        for (int cell = 0; cell < SIZE_ARRAY_CELL; cell++)
        {
            auto const map_e = arcade.newEntity();
            auto const map_a = arcade.newAsset();
            std::string tile = "./assets/Minesweeper/textures/";
            switch (this->_mapDisplay.at(row).at(cell))
            {
                case '_':
                    tile += "block1.png";
                    break;
                case '1':
                    tile += "1.png";
                    break;
                case '2':
                    tile += "2.png";
                    break;
                case '3':
                    tile += "3.png";
                    break;
                case '4':
                    tile += "4.png";
                    break;
                case '5':
                    tile += "5.png";
                    break;
                case '6':
                    tile += "6.png";
                    break;
                case '7':
                    tile += "7.png";
                    break;
                case '8':
                    tile += "8.png";
                    break;
                case 'B':
                    tile += "mine.png";
                    break;
                case 'F':
                    tile += "flag.png";
                    break;
                case '|':
                    tile += "block2.png";
                    break;
                default:
                    tile += "block.png";
            }
            map_a->setTexturePath(tile);
            map_a->setAlternateRender(this->_mapDisplay[row][cell]);
            map_e->setPos(ANAL::Vector2(cell + 1, row + 7));
            map_e->setAsset(*map_a);
            renderer.drawEntity(*map_e);
        }
    }
    renderer.drawText("Flags : " + std::to_string(this->_flags), ANAL::Vector2(2, 2));
    renderer.drawText("Player: " + this->m_player_name, ANAL::Vector2(2, 3));
    renderer.drawText("Best: " + std::to_string(this->m_bestscore), ANAL::Vector2(2, 4));
    static int frame = 0;
    frame++;
    if (this->getState() == WIN && this->_bombflagged == NUMBER_OF_BOMBS && this->_flags == 0)
    {
        if (this->_bombflagged > this->m_bestscore)
	        this->m_bestscore = this->_bombflagged;
        if ((frame / 20) % 2 == 0)
        {
            renderer.drawText("Win", ANAL::Vector2(12, 25));
            renderer.drawText("Player: " + this->m_player_name, ANAL::Vector2(12, 26));
            renderer.drawText("Score: " + std::to_string(this->_bombflagged), ANAL::Vector2(12, 27));
            renderer.drawText("Best: " + std::to_string(this->m_bestscore), ANAL::Vector2(12, 28));
            renderer.drawText("Press R to restart", ANAL::Vector2(12, 29));
        }
    } else if (this->getState() == DEFEAT && this->_board.bombDiscover() == true) {
        if (this->_bombflagged > this->m_bestscore)
	        this->m_bestscore = this->_bombflagged;
        if ((frame / 20) % 2 == 0)
        {
            renderer.drawText("Game Over", ANAL::Vector2(12, 25));
            renderer.drawText("Player: " + this->m_player_name, ANAL::Vector2(12, 26));
            renderer.drawText("Score: " + std::to_string(this->_bombflagged), ANAL::Vector2(12, 27));
            renderer.drawText("Best: " + std::to_string(this->m_bestscore), ANAL::Vector2(12, 28));
            renderer.drawText("Press R to restart", ANAL::Vector2(12, 29));
        }
    }
    if (frame >= 6000)
        frame = 0;
    renderer.render();
}

extern "C" std::unique_ptr<ANAL::IGame> uwu_entrypoint_game(void) { return std::make_unique<Minesweeper::Game>(); }

ANAL::ModuleVersion uwu_get_module_version() { return ANAL::ModuleVersion::V1_1_0; }

ANAL::ModuleType uwu_get_module_type() { return ANAL::ModuleType::GAME; }