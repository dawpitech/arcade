/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** Arcade.hpp
*/

#ifndef MINESWEEPER_HPP
    #define MINESWEEPER_HPP

    #define EXIT_FAILURE_TECH 84
    #define SIZE_ARRAY 8
    #define NUMBER_OF_BOMBS 10

    #include <array>

    #include "ANAL/IGame.hpp"
    #include "ANAL/IRenderer.hpp"


namespace Minesweeper
{
    class Mines : Game
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

    class Board : public Game
    {
        public:
            Board();
            ~Board() = default;
            const std::array<std::array<Minesweeper::Mines, SIZE_ARRAY>, SIZE_ARRAY> &getMap() const;
            bool verifMapIsEmpty(std::array<std::array<Minesweeper::Mines, SIZE_ARRAY>, SIZE_ARRAY>);
            void initializeMap();
            void clearMap();
            void placeMine();
            void adjacentBombs();

        private:
            int conditionAdjacent(int, int);
            std::array<std::array<Minesweeper::Mines, SIZE_ARRAY>, SIZE_ARRAY> _map;
    };

    class Game : public ANAL::IGame
    {
        public:
            Game() = default;
            ~Game() override = default;
            bool checkGame();
            bool restartGame();
            int mainGame();

            void processEvents(std::vector<ANAL::Event> &) override;
            void compute() override;
            void render(ANAL::IRenderer &renderer, ANAL::IArcade &arcade) override;

        private:
            bool restart = false;
    };
} // namespace Minesweeper

#endif // MINESWEEPER_HPP
