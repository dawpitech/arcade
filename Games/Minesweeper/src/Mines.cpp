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
    for (auto &row : _map) {
        for (auto &cell : row) {
            cell.setBomb(false);
            cell.setFlag(false);
            cell.setNumber(0);
            cell.setVisible(false);
        }
    }

    placeMine();
    adjacentBombs();
}

void Minesweeper::Board::placeMine()
{
    srand(time(0));
    int minesPlaced = 0;
    while (minesPlaced < NUMBER_OF_BOMBS) {
        int cell = rand() % SIZE_ARRAY_CELL;
        int row = rand() % SIZE_ARRAY_ROW;
        if (!_map[row][cell].getBomb()) {
            _map[row][cell].setBomb(true);
            minesPlaced++;
        }
    }
}

int Minesweeper::Board::conditionAdjacent(int row, int cell)
{
    int count = 0;

    // Vérifiez les limites avant d'accéder aux éléments
    if (row > 0 && cell > 0 && _map[row - 1][cell - 1].getBomb())
        count++;
    if (row > 0 && _map[row - 1][cell].getBomb())
        count++;
    if (row > 0 && cell < _map[0].size() - 1 && _map[row - 1][cell + 1].getBomb())
        count++;

    // middle-line
    if (cell > 0 && _map[row][cell - 1].getBomb())
        count++;
    if (cell < _map[0].size() - 1 && _map[row][cell + 1].getBomb())
        count++;

    // down-line
    if (row < _map.size() - 1 && cell > 0 && _map[row + 1][cell - 1].getBomb())
        count++;
    if (row < _map.size() - 1 && _map[row + 1][cell].getBomb())
        count++;
    if (row < _map.size() - 1 && cell < _map[0].size() - 1 && _map[row + 1][cell + 1].getBomb())
        count++;

    return count;
}

void Minesweeper::Board::adjacentBombs()
{
    for (size_t row = 0; row < _map.size(); ++row) {
        for (size_t cell = 0; cell < _map[row].size(); ++cell) {
            if (_map[row][cell].getBomb())
                continue;
            int count = 0;
            count = conditionAdjacent(row, cell);
            _map[row][cell].setNumber(count);
        }
    }
}

bool Minesweeper::Board::verifMapIsEmpty(std::array<std::array<Minesweeper::Mines, SIZE_ARRAY_CELL>, SIZE_ARRAY_ROW> _map)
{
    for (const auto &row : _map) {
        for (const auto &cell : row) {
            if (cell.getBomb() || cell.getFlag() || cell.getVisible() || cell.getNumber() != 0)
                return false;
        }
    }
    return true;
}

void Minesweeper::Board::clearMap()
{
    if (!verifMapIsEmpty(_map)) {
        for (auto &row : _map) {
            for (auto &cell : row)
                cell.reset();
        }
    }
}

bool Minesweeper::Board::isBomb(ANAL::Vector2<int> _coor)
{
    if (this->_map[_coor.y][_coor.x].getBomb() == true)
        return true;
    return false;
}

bool Minesweeper::Board::isFlag(ANAL::Vector2<int> _coor)
{
    if (this->_map[_coor.y][_coor.x].getFlag() == true)
        return true;
    return false;
}

bool Minesweeper::Board::isVisible(ANAL::Vector2<int> _coor)
{
    if (this->_map[_coor.y][_coor.x].getVisible() == true)
        return true;
    return false;
}

int Minesweeper::Board::isNumber(ANAL::Vector2<int> _coor)
{
    if (this->_map[_coor.y][_coor.x].getNumber() >= 1)
        return this->_map[_coor.y][_coor.x].getNumber();
    return 0;
}

std::vector<std::string> Minesweeper::Board::mapToDisplay(std::array<std::array<Minesweeper::Mines, SIZE_ARRAY_CELL>, SIZE_ARRAY_ROW> _map) {
    std::vector<std::string> _mapdisplay;

    for (const auto& row : _map) {
        std::string cellStr;
        for (const auto& cell : row) {
            if (cell.getVisible()) {
                if (cell.getBomb()) {
                    printf("bombbbb\n");
                    cellStr += 'B';
                } else if (cell.getFlag()) {
                    cellStr += cell.getFlag() ? 'F' : '|';
                } else {
                    int count = cell.getNumber();
                    cellStr += (count > 0) ? ('0' + count) : '|';
                }
            } else {
                cellStr += '_';
            }
        }
        for (auto it : cellStr)
            std::cout << it;
        printf("\n");
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

void Minesweeper::Game::toVisible(int _coorX, int _coorY)
{
    std::cout << "------->>>>> " << this->_map[_coorX][_coorY].getVisible() << std::endl;
    if (this->_map[_coorX][_coorY].getVisible() == false)
        this->_map[_coorX][_coorY].setVisible(true);
}
