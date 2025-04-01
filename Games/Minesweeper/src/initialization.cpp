/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** Arcade.cpp
*/

#include "Minesweeper.hpp"

Minesweeper::Board::Board()
{
    clearMap();
    initializeMap();
}

void Minesweeper::Board::initializeMap()
{
    for (auto& row : _map) {
        for (auto& cell : row) {
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
    while (minesPlaced < NUMBEROFBOMBS) {
        int x = rand() % SIZEARRAY;
        int y = rand() % SIZEARRAY;
        if (!_map[y][x].getBomb()) {
            _map[y][x].setBomb(true);
            minesPlaced ++;
        }
    }
}

int Minesweeper::Board::conditionAdjacent(int y, int x)
{
    int count = 0;

    //Up-line
    if (_map[y - 1][x - 1].getBomb() == true)
        count + 1;
    if (_map[y - 1][x].getBomb() == true)
        count + 1;
    if (_map[y - 1][x + 1].getBomb() == true)
        count + 1;

    //middle-line
    if (_map[y][x - 1].getBomb() == true)
        count + 1;
    if (_map[y][x - 1].getBomb() == true)
        count + 1;

    //down-line
    if (_map[y + 1][x - 1].getBomb() == true)
        count + 1;
    if (_map[y + 1][x].getBomb() == true)
        count + 1;
    if (_map[y + 1][x + 1].getBomb() == true)
        count + 1;
    return count;
}

void Minesweeper::Board::adjacentBombs()
{
    for (int y = 0; y < SIZEARRAY; y ++) {
        for (int x = 0; x < SIZEARRAY; x ++) {
            if (_map[y][x].getBomb())
                continue;
            int count = 0;
            count = conditionAdjacent(y, x);
            _map[y][x].setNumber(count);
        }
    }
}

bool Minesweeper::Board::verifMapIsEmpty(std::array<std::array<Minesweeper::Mines, SIZEARRAY>, SIZEARRAY> _map)
{
    for (const auto& row : _map) {
        for (const auto& cell : row) {
            if (cell.getBomb() || cell.getFlag() || cell.getVisible() || cell.getNumber() != 0)
                return false;
        }
    }
    return true;
}

void Minesweeper::Board::clearMap()
{
    if (!verifMapIsEmpty(_map)) {
        for (auto& row : _map) {
            for (auto& cell : row) {
                cell.reset();
            }
        }
    }
}
