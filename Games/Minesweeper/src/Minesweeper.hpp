/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** Arcade.hpp
*/

#ifndef MINESWEEPER_HPP
    #define MINESWEEPER_HPP

    #define EXIT_FAILURE_TECH 84
    #define SIZE_ARRAY_ROW 16
    #define SIZE_ARRAY_CELL 30
    #define NUMBER_OF_BOMBS 99

    #include <array>
    #include <cstdio>

    #include "ANAL/Vector2.hpp"
    #include "ANAL/IGame.hpp"


namespace Minesweeper
{
    class Mines
    {
        public:
            Mines() = default;
            ~Mines() = default;

            bool getVisible() const { return visible; }
            bool getBomb() const { return bomb; }
            bool getFlag() const { return flag; }
            int getNumber() const { return number; }

            void setVisible(bool isVisible) { visible = isVisible; }
            void setBomb(bool isBomb) { bomb = isBomb; }
            void setFlag(bool isFlag) { flag = isFlag; }
            void setNumber(int isNumber) { number = isNumber; }

            void reset()
            {
                visible = false;
                bomb = false;
                flag = false;
                number = 0;
            }

        private:
            bool visible = false;
            bool bomb = false;
            bool flag = false;
            int number = 0;
    };

    class Board : public Mines
    {
        public:
            Board();
            ~Board() = default;
            const std::array<std::array<Minesweeper::Mines, SIZE_ARRAY_CELL>, SIZE_ARRAY_ROW> &getMap() const;
            bool verifMapIsEmpty(std::array<std::array<Minesweeper::Mines, SIZE_ARRAY_CELL>, SIZE_ARRAY_ROW>);
            void initializeMap();
            void clearMap();
            void placeMine();
            void adjacentBombs();

            bool isBomb(ANAL::Vector2<int>);
            bool isFlag(ANAL::Vector2<int>);
            bool isVisible(ANAL::Vector2<int>);
            int isNumber(ANAL::Vector2<int>);

            std::vector<std::string> mapToDisplay(std::array<std::array<Minesweeper::Mines, SIZE_ARRAY_CELL>, SIZE_ARRAY_ROW>);

            bool win();
            bool bombDiscover();

        private:
            int conditionAdjacent(int, int);
            std::array<std::array<Minesweeper::Mines, SIZE_ARRAY_CELL>, SIZE_ARRAY_ROW> _map;
    };

    class Game : public ANAL::IGame
    {
        public:
            Game();
            ~Game() = default;
            
            void processEvents(std::vector<ANAL::Event>&) override;
            void compute(ANAL::IArcade& arcade) override;
            void render(ANAL::IRenderer& renderer, const ANAL::IArcade& arcade) override;
            
        private:
            void init();
            void restart();
            void toVisible(int _coorX, int _coorY);

            Board _board;
            std::array<std::array<Minesweeper::Mines, SIZE_ARRAY_CELL>, SIZE_ARRAY_ROW> _map;
            std::vector<std::string> _mapDisplay;
            ANAL::Vector2<int> _coor{0, 0};
            bool _leftKey = false;
            bool _rightKey = false;
            int _bombflagged = 0;
            int _flags = 10;
    };
} // namespace Minesweeper

#endif // MINESWEEPER_HPP
