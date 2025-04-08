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

void Minesweeper::Game::init()
{
    this->_board = Board();
    this->_flags = 10;
}

void Minesweeper::Game::restart()
{
    this->_board.clearMap();
    this->_flags = 10;
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
                    _left = click_mouse ? true : false;
                    _new_coor = e.mouseEvent.value().coords;
                }
                if (mouse == ANAL::MouseKeys::RIGHT_CLICK) {
                    _right == click_mouse ? true : false;
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
                    this->restart();
                break;
            }
            default:
                break;
        }
    }
    this->_leftKey = _left;
    this->_rightKey = _right;
    this->_coor = _new_coor;
    printf("coor.y -> %d | coor.x -> %d\n", this->_coor.y, this->_coor.x);
}

void Minesweeper::Game::compute(ANAL::IArcade& arcade) {
    if (this->_leftKey == true) {
        printf("isbomb -> %b\n", this->_board.isBomb(this->_coor));
        if (this->_board.isBomb(this->_coor) == true) {
            toVisible(this->_coor.x, this->_coor.y);
            printf("getvisible -> %b\n", this->_map[this->_coor.y][this->_coor.x].getVisible());
        }
        toVisible(this->_coor.x, this->_coor.y);
    }
    if (this->_rightKey == true) {
        if (this->_board.isFlag(this->_coor) == true) {
            this->_board.setFlag(true);
            this->_flags = this->_flags - 1;
            this->_bombflagged = this->_bombflagged + 1;
            toVisible(this->_coor.x, this->_coor.y);
        }
    }
    this->_mapDisplay = this->_board.mapToDisplay(this->_map);
}

void Minesweeper::Game::render(ANAL::IRenderer &renderer, const ANAL::IArcade &arcade) {
    renderer.clear();
    renderer.setWindowTitle("Minesweeper");
    for (int row = 0; row < SIZE_ARRAY_ROW; row++)
    {
        for (int cell = 0; cell < SIZE_ARRAY_CELL; cell++)
        {
            auto const map_e = arcade.newEntity();
            auto const map_a = arcade.newAsset();
            std::string tile = "./assets/Minesweeper/textures/";
            switch (this->_mapDisplay[row][cell])
            {
                case '_':
                    tile += "block.png";
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
            // map_e->setPos(ANAL::Vector2(row + 8, cell + 1));
            map_e->setPos(ANAL::Vector2(row, cell));
            map_e->setAsset(*map_a);
            renderer.drawEntity(*map_e);
        }
    }
    renderer.drawText("Flags : " + std::to_string(this->_flags), ANAL::Vector2(2, 2));
    if (this->_board.win() == true && this->_bombflagged == 10) {
        renderer.drawText("Win", ANAL::Vector2(13, 13));
        renderer.drawText("Press R to restart", ANAL::Vector2(12, 14));
    } else if (this->_board.win() == false && this->_board.bombDiscover() == true) {
        renderer.drawText(" Game Over", ANAL::Vector2(13, 13));
        renderer.drawText("Press R to restart", ANAL::Vector2(12, 14));
    }
    renderer.render();
}

extern "C" std::unique_ptr<ANAL::IGame> uwu_entrypoint_game(void) { return std::make_unique<Minesweeper::Game>(); }

ANAL::ModuleVersion uwu_get_module_version() { return ANAL::ModuleVersion::V1_1_0; }

ANAL::ModuleType uwu_get_module_type() { return ANAL::ModuleType::GAME; }