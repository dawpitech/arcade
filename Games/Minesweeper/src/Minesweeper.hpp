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
            std::array<std::array<Minesweeper::Mines, SIZE_ARRAY_CELL>, SIZE_ARRAY_ROW>& getMap() { return _map; };
            bool verifMapIsEmpty();
            void initializeMap();
            void clearMap();
            void placeMine();
            void adjacentBombs();

            bool isBomb(ANAL::Vector2<int>);
            bool isFlag(ANAL::Vector2<int>);
            bool isVisible(ANAL::Vector2<int>);
            int isNumber(ANAL::Vector2<int>);

            std::vector<std::string> mapToDisplay();

            bool win();
            bool bombDiscover();

            void mapVisible();
            void toVisible(int _coorX, int _coorY);

            void toFlag(int, int);

        private:
            int conditionAdjacent(int, int);
            std::array<std::array<Minesweeper::Mines, SIZE_ARRAY_CELL>, SIZE_ARRAY_ROW> _map = {};
    };

    class Game : public ANAL::IGame
    {
        public:
            enum STATE {
                RESTART,
                HAS_RESTART,
                EMPTY_MAP,
                WORKS,
                DEFEAT,
                WIN
            };
            enum CLICK {
                RIGHT,
                LEFT,
                UNKNOWN
            };
            Game();
            ~Game() = default;
            
            void processEvents(std::vector<ANAL::Event>&) override;
            void compute(ANAL::IArcade& arcade) override;
            void render(ANAL::IRenderer& renderer, const ANAL::IArcade& arcade) override;
            
            const STATE getState() { return this->m_state; };
            const CLICK getClick() { return this->m_click; };

        private:
            void init();
            void restart();
            int bBF();

            Board _board;
            STATE m_state;
            CLICK m_click;
            std::vector<std::string> _mapDisplay = {};
            ANAL::Vector2<int> _coor{0, 0};
            bool _fClick = true;
            int _bombflagged = 0;
            int _flags = NUMBER_OF_BOMBS;
    };
} // namespace Minesweeper

#endif // MINESWEEPER_HPP
