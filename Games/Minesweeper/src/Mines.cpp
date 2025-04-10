/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** Arcade.cpp
*/

#include <iostream>

#include "Minesweeper.hpp"

Minesweeper::Board::Board() { initializeMap(); }

void Minesweeper::Board::initializeMap()
{
    placeMine();
    adjacentBombs();
}

void Minesweeper::Board::placeMine()
{
    srand(time(nullptr));
    int minesPlaced = 0;
    while (minesPlaced < Minesweeper::NUMBER_OF_BOMBS) {
        const int cell = rand() % SIZE_ARRAY_CELL;
        const int row = rand() % SIZE_ARRAY_ROW;
        if (auto &map = getMap(); !map.at(row).at(cell).isBomb()) {
            this->getCell(ANAL::Vector2{cell, row}).setBomb(true);
            minesPlaced++;
        }
    }
}

int Minesweeper::Board::conditionAdjBomb(const ANAL::Vector2<int>& coords)
{
    int count = 0;

    //up
    if (coords.y > 0 && coords.x > 0 && this->getCell(ANAL::Vector2{coords.x - 1, coords.y - 1}).isBomb())
        count++;
    if (coords.y > 0 && this->getCell(ANAL::Vector2{coords.x, coords.y - 1}).isBomb())
        count++;
    if (coords.y > 0 && coords.x + 1 < SIZE_ARRAY_CELL && this->getCell(ANAL::Vector2{coords.x + 1, coords.y - 1}).isBomb())
        count++;

    //middle
    if (coords.x > 0 && this->getCell(ANAL::Vector2{coords.x - 1, coords.y}).isBomb())
        count++;
    if (coords.x + 1 < SIZE_ARRAY_CELL && this->getCell(ANAL::Vector2{coords.x + 1, coords.y}).isBomb())
        count++;

    //down
    if (coords.y + 1 < SIZE_ARRAY_ROW && coords.x > 0 && this->getCell(ANAL::Vector2{coords.x - 1, coords.y + 1}).isBomb())
        count++;
    if (coords.y + 1 < SIZE_ARRAY_ROW && this->getCell(ANAL::Vector2{coords.x, coords.y + 1}).isBomb())
        count++;
    if (coords.y + 1 < SIZE_ARRAY_ROW && coords.x + 1 < SIZE_ARRAY_CELL && this->getCell(ANAL::Vector2{coords.x + 1, coords.y + 1}).isBomb())
        count++;

    return count;
}

void Minesweeper::Board::adjacentBombs()
{
    for (size_t row = 0; row < this->getMap().size(); ++row) {
        for (size_t cell = 0; cell < this->getMap().at(row).size(); ++cell) {
            if (this->getMap().at(row).at(cell).isBomb())
                continue;
            const auto coords = ANAL::Vector2{
                static_cast<int>(cell),
                static_cast<int>(row),
            };
            this->getCell(coords).setNumber(conditionAdjBomb(coords));
        }
    }
}

Minesweeper::Cell &Minesweeper::Board::getCell(const ANAL::Vector2<int> &coords)
{
    return this->_map.at(coords.y).at(coords.x);
}

std::vector<std::string> Minesweeper::Board::mapToDisplay() {
    std::vector<std::string> _mapDisplay;

    for (const auto& row : this->getMap()) {
        std::string cellStr;
        for (const auto& cell : row) {
            if (cell.isVisible()) {
                if (cell.isBomb() && !cell.isFlag()) {
                    cellStr += 'B';
                } else {
                    const char count = static_cast<char>(cell.getNumber());
                    cellStr += count > 0
                        ? '0' + count
                        : '.';
                }
            } else {
                cellStr += (cell.isFlag() || (cell.isBomb() && cell.isFlag()) || (cell.isFlag() && cell.getNumber() >= 1))
                    ? 'F'
                    : '_';
            }
        }
        _mapDisplay.push_back(cellStr);
    }
    return _mapDisplay;
}

void Minesweeper::Board::toVisible(const ANAL::Vector2<int>& coords)
{
    this->getMap().at(coords.y).at(coords.x).setVisible(true);
}

void Minesweeper::Board::mapVisible()
{
    for (auto &row : this->getMap()) {
        for (auto &cell : row)
            cell.setVisible(true);
    }
}
