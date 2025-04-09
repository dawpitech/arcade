/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** Arcade.cpp
*/

#include "Minesweeper.hpp"
#include <iostream>

Minesweeper::Board::Board() { initializeMap(); }

void Minesweeper::Board::initializeMap()
{
    auto& _map = getMap();
    placeMine();
    adjacentBombs();
}

void Minesweeper::Board::placeMine()
{
    srand(time(nullptr));
    int minesPlaced = 0;
    while (minesPlaced < NUMBER_OF_BOMBS) {
        int cell = rand() % SIZE_ARRAY_CELL;
        int row = rand() % SIZE_ARRAY_ROW;
        auto& map = getMap();
        if (!map.at(row).at(cell).getBomb()) {
            map[row][cell].setBomb(true);
            minesPlaced++;
        }
    }
}

int Minesweeper::Board::conditionAdjacent(int row, int cell)
{
    int count = 0;

    //up
    if (row > 0 && cell > 0 && this->getMap().at(row - 1).at(cell - 1).getBomb())
        count++;
    if (row > 0 && this->getMap().at(row - 1).at(cell).getBomb())
        count++;
    if (row > 0 && cell < this->getMap().at(0).size() - 1 && this->getMap().at(row - 1).at(cell + 1).getBomb())
        count++;

    //middle
    if (cell > 0 && this->getMap().at(row).at(cell - 1).getBomb())
        count++;
    if (cell < this->getMap().at(0).size() - 1 && this->getMap().at(row).at(cell + 1).getBomb())
        count++;

    //down
    if (row < this->getMap().size() - 1 && cell > 0 && this->getMap().at(row + 1).at(cell - 1).getBomb())
        count++;
    if (row < this->getMap().size() - 1 && this->getMap().at(row + 1).at(cell).getBomb())
        count++;
    if (row < this->getMap().size() - 1 && cell < this->getMap().at(0).size() - 1 && this->getMap().at(row + 1).at(cell + 1).getBomb())
        count++;

    return count;
}

void Minesweeper::Board::adjacentBombs()
{
    for (size_t row = 0; row < this->getMap().size(); ++row) {
        for (size_t cell = 0; cell < this->getMap().at(row).size(); ++cell) {
            if (this->getMap().at(row).at(cell).getBomb())
                continue;
            int count = 0;
            count = conditionAdjacent(row, cell);
            this->getMap().at(row).at(cell).setNumber(count);
        }
    }
}

bool Minesweeper::Board::verifMapIsEmpty()
{
    for (const auto &row : getMap()) {
        for (const auto &cell : row) {
            if (cell.getBomb() || cell.getFlag() || cell.getVisible() || cell.getNumber() != 0)
                return false;
        }
    }
    return true;
}

void Minesweeper::Board::clearMap()
{
    if (!verifMapIsEmpty()) {
        for (auto &row : this->getMap()) {
            for (auto &cell : row)
                cell.reset();
        }
    }
}

bool Minesweeper::Board::isBomb(ANAL::Vector2<int> _coor)
{
    if (this->getMap().at(_coor.y).at(_coor.x).getBomb() == true)
        return true;
    return false;
}

bool Minesweeper::Board::isFlag(ANAL::Vector2<int> _coor)
{
    if (this->getMap().at(_coor.y).at(_coor.x).getFlag() == true)
        return true;
    return false;
}

bool Minesweeper::Board::isVisible(ANAL::Vector2<int> _coor)
{
    if (this->getMap().at(_coor.y).at(_coor.x).getVisible() == true)
        return true;
    return false;
}

int Minesweeper::Board::isNumber(ANAL::Vector2<int> _coor)
{
    if (this->getMap().at(_coor.y).at(_coor.x).getNumber() >= 1)
        return this->_map[_coor.y][_coor.x].getNumber();
    return 0;
}

std::vector<std::string> Minesweeper::Board::mapToDisplay() {
    std::vector<std::string> _mapdisplay;

    for (const auto& row : this->getMap()) {
        std::string cellStr;
        for (const auto& cell : row) {
            if (cell.getVisible()) {
                if (cell.getBomb() && !cell.getFlag()) {
                    cellStr += 'B';
                } else if (cell.getFlag() || (cell.getBomb() && cell.getFlag()) || (cell.getFlag() && cell.getNumber() >= 1)) {
                    cellStr += 'F';
                    continue;
                } else {
                    int count = cell.getNumber();
                    cellStr += (count > 0) ? ('0' + count) : '|';
                }
            } else {
                cellStr += '_';
            }
        }
        _mapdisplay.push_back(cellStr);
    }
    return _mapdisplay;
}

bool Minesweeper::Board::win() {
    int count = 0;
    for (const auto &row : _map) {
        for (const auto &cell : row) {
            if (cell.getFlag() == true && cell.getBomb() == true)
                count ++;
        }
    }
    if (count == 10)
        return true;
    return false;
}

bool Minesweeper::Board::bombDiscover() {
    for (const auto &row : _map) {
        for (const auto &cell : row) {
            if (cell.getVisible() == true && cell.getBomb() == true)
                return true;
        }
    }
    return false;
}

void Minesweeper::Board::toVisible(int _coorX, int _coorY)
{
    if (this->getMap().at(_coorY).at(_coorX).getVisible() == false)
        this->getMap().at(_coorY).at(_coorX).setVisible(true);
}

void Minesweeper::Board::toFlag(int _coorX, int _coorY)
{
    if (this->getMap().at(_coorY).at(_coorX).getFlag() == false) {
        this->getMap().at(_coorY).at(_coorX).setVisible(true);
        this->getMap().at(_coorY).at(_coorX).setFlag(true);
    }
}

void Minesweeper::Board::mapVisible()
{
    for (auto &row : this->getMap()) {
        for (auto &cell : row)
            cell.setVisible(true);
    }
}

int Minesweeper::Game::bBF()
{
    if (this->_board.getMap().at(this->_coor.y).at(this->_coor.x).getBomb() == true && this->_board.getMap().at(this->_coor.y).at(this->_coor.x).getFlag() == true)
        return 1;
    return 0;
}
