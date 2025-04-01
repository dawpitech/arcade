/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** Arcade.hpp
*/

#ifndef MINESWEEPER_HPP
    #define MINESWEEPER_HPP

    #define EXIT_FAILURE_TECH 84
    #define SIZEARRAY 8 
    #define NUMBEROFBOMBS 10

    #include <iostream>
    #include <algorithm>
    #include <array>
    #include <ANAL/IGame.hpp>
    #include <ANAL/IRenderer.hpp>

namespace Minesweeper
{
    class Mines : public Game
    {
        public:
            bool getVisible() const { return visible; }
            bool getBomb() const { return bomb; }
            bool getFlag() const { return flag; }
            int getNumber() const { return number; }

            void setVisible(bool isVisible) { visible = isVisible; }
            void setBomb(bool isBomb) { bomb = isBomb; }
            void setFlag(bool isFlag) { flag = isFlag; }
            void setNumber(bool isNumber) { number = isNumber; }

            void reset() {visible = false; bomb = false; flag = false; number = 0;}

        private:
            bool visible = false;
            bool bomb = false;
            bool flag = false;
            int number = 0;
    };
    class Board : public Game
    {
        public:
            Board();
            ~Board() = default;
            const std::array<std::array<Minesweeper::Mines, SIZEARRAY>, SIZEARRAY>& getMap() const;
            bool verifMapIsEmpty(std::array<std::array<Minesweeper::Mines, SIZEARRAY>, SIZEARRAY>);
            void initializeMap();
            void clearMap();
            void placeMine();
            void adjacentBombs();
        private:
            int conditionAdjacent(int, int);
            std::array<std::array<Minesweeper::Mines, SIZEARRAY>, SIZEARRAY> _map;
    };
    class Game : public ANAL::IGame
    {
        public:
            Game() = default;
            ~Game() = default;
            bool checkGame();
            bool restartGame();
            int mainGame();

            void processEvents(const std::vector<ANAL::Event>&) override;
            void compute() override;
            void render(ANAL::IRenderer& renderer) override;
        private:
            bool restart = false;
    };
}

#endif //MINESWEEPER_HPP
