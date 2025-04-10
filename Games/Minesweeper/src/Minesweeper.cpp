/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** Arcade.cpp
*/

#include <algorithm>
#include <string>

#include "Minesweeper.hpp"
#include "ANAL/Events.hpp"
#include "ANAL/IModule.hpp"
#include "ANAL/Vector2.hpp"

void Minesweeper::Minesweeper::init()
{
    this->_board = Board();
    this->_state = RUNNING;
    this->_flags = NUMBER_OF_BOMBS;
    this->_bombFlagged = 0;
    this->_board.initializeMap();
}

void Minesweeper::Minesweeper::processEvents(std::vector<ANAL::Event> &ev)
{
    for (const auto &[type, keyEvent, mouseEvent, closeEvent] : ev)
    {
        switch (type)
        {
            case ANAL::EventType::MOUSE:
                {
                    if (this->getState() != RUNNING)
                        continue;
                    const ANAL::Vector2 gridClickPos{
                        std::clamp(mouseEvent->coords.x - 1, 0, static_cast<int>(Board::SIZE_ARRAY_CELL - 1)),
                        std::clamp(mouseEvent->coords.y - 7, 0, static_cast<int>(Board::SIZE_ARRAY_ROW - 1)),
                    };
                    auto& cell = this->_board.getCell(gridClickPos);
                    switch (mouseEvent->state)
                    {
                        case ANAL::State::PRESSED:
                            this->_lastClickPos = mouseEvent->coords;
                            continue;
                        case ANAL::State::RELEASED:
                            if (this->_lastClickPos.x != mouseEvent->coords.x || this->_lastClickPos.y != mouseEvent->coords.y)
                                continue;
                            break;
                    }
                    switch (mouseEvent->key)
                    {
                        case ANAL::MouseKeys::LEFT_CLICK:
                            if (cell.isFlag())
                                continue;
                            if (this->_firstClick && cell.isBomb()) {
                                this->restart();
                                return;
                            }
                            if (cell.isBomb())
                                this->_state = DEFEAT;
                            this->_board.toVisible(gridClickPos);
                            this->_firstClick = false;
                            break;
                        case ANAL::MouseKeys::RIGHT_CLICK:
                            if (cell.isVisible() || this->_firstClick)
                                continue;
                            if (!cell.isFlag()) {
                                cell.setFlag(true);
                                this->_flags -= 1;
                                this->_bombFlagged += cell.isBomb() ? 1 : 0;
                            } else {
                                cell.setFlag(false);
                                this->_flags += 1;
                                this->_bombFlagged -= cell.isBomb() ? 1 : 0;
                            }
                            break;
                        default:
                            break;
                    }
                }
            case ANAL::EventType::KEYBOARD:
                if (keyEvent->key == ANAL::Keys::KEY_R)
                    this->_state = RESTARTING;
                break;
            default:
                break;
        }
    }
}

void Minesweeper::Minesweeper::compute(ANAL::IArcade &arcade)
{
    if (this->_playername.empty()) {
        this->_playername = arcade.getPlayerName();
        this->_bestScore = arcade.getPlayerHighscore(this->_playername);
    }

    switch (this->getState())
    {
        case DEFEAT:
            this->_board.mapVisible();
            this->_currentMap = this->_board.mapToDisplay();
            break;
        case RESTARTING:
            this->restart();
            this->_firstClick = true;
            this->_state = RUNNING;
            break;
        default:
            break;
    }
    if (this->_bombFlagged == NUMBER_OF_BOMBS && this->_flags == 0)
        this->setState(WIN);

    if (this->getState() == WIN || this->getState() == DEFEAT)
        if (this->_bombFlagged > this->_bestScore) {
            this->_bestScore = this->_bombFlagged;
            arcade.setPlayerHighscore(this->_bestScore);
        }
}

void Minesweeper::Minesweeper::render(ANAL::IRenderer &renderer, const ANAL::IArcade &arcade)
{
    this->_frame++;
    this->_currentMap = this->_board.mapToDisplay();

    renderer.clear();
    renderer.setWindowTitle("Minesweeper");

    for (int row_idx = 0; row_idx < Board::SIZE_ARRAY_ROW; row_idx++) {
        for (int cell_idx = 0; cell_idx < Board::SIZE_ARRAY_CELL; cell_idx++) {
            const auto entity = arcade.newEntity();
            const auto asset = arcade.newAsset();
            std::string assetPath = "./assets/Minesweeper/textures/";
            switch (this->_currentMap.at(row_idx).at(cell_idx))
            {
                case '_':
                    assetPath += "block1.png";
                    break;
                case '1':
                    assetPath += "1.png";
                    break;
                case '2':
                    assetPath += "2.png";
                    break;
                case '3':
                    assetPath += "3.png";
                    break;
                case '4':
                    assetPath += "4.png";
                    break;
                case '5':
                    assetPath += "5.png";
                    break;
                case '6':
                    assetPath += "6.png";
                    break;
                case '7':
                    assetPath += "7.png";
                    break;
                case '8':
                    assetPath += "8.png";
                    break;
                case 'B':
                    assetPath += "mine.png";
                    break;
                case 'F':
                    assetPath += "flag.png";
                    break;
                case '.':
                    assetPath += "block2.png";
                    break;
                default:
                    assetPath += "block.png";
            }
            asset->setTexturePath(assetPath);
            asset->setAlternateRender(this->_currentMap.at(row_idx).at(cell_idx));
            entity->setPos(ANAL::Vector2(cell_idx + 1, row_idx + 7));
            entity->setAsset(*asset);
            renderer.drawEntity(*entity);
        }
    }

    renderer.drawText("Flags : " + std::to_string(this->_flags), ANAL::Vector2(2, 2));
    renderer.drawText("Player: " + this->_playername, ANAL::Vector2(2, 3));
    renderer.drawText("Best: " + std::to_string(this->_bestScore), ANAL::Vector2(2, 4));

    if (this->getState() == WIN || this->getState() == DEFEAT) {
        if (this->_frame / 20 % 2 == 0) {
            renderer.drawText(this->getState() == WIN ? "Win" : "Defeat", ANAL::Vector2(12, 25));
            renderer.drawText("Player: " + this->_playername, ANAL::Vector2(12, 26));
            renderer.drawText("Score: " + std::to_string(this->_bombFlagged), ANAL::Vector2(12, 27));
            renderer.drawText("Best: " + std::to_string(this->_bestScore), ANAL::Vector2(12, 28));
            renderer.drawText("Press R to restart", ANAL::Vector2(12, 29));
        }
    }

    renderer.render();
}

extern "C" std::unique_ptr<ANAL::IGame> uwu_entrypoint_game(void) { return std::make_unique<Minesweeper::Minesweeper>(); }

ANAL::ModuleVersion uwu_get_module_version() { return ANAL::ModuleVersion::V1_1_0; }
ANAL::ModuleType uwu_get_module_type() { return ANAL::ModuleType::GAME; }
