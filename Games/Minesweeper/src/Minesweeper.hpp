/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** Arcade.hpp
*/

#ifndef MINESWEEPER_HPP
    #define MINESWEEPER_HPP

    #define EXIT_FAILURE_TECH 84

    #include <array>
    #include <cstdio>

    #include "ANAL/IGame.hpp"
    #include "ANAL/Vector2.hpp"

namespace Minesweeper
{
    class Cell
    {
        public:
            Cell() = default;
            ~Cell() = default;

            [[nodiscard]] bool isVisible() const { return visible; }
            [[nodiscard]] bool isBomb() const { return bomb; }
            [[nodiscard]] bool isFlag() const { return flag; }
            [[nodiscard]] int getNumber() const { return number; }

            void setVisible(const bool isVisible) { visible = isVisible; }
            void setBomb(const bool isBomb) { bomb = isBomb; }
            void setFlag(const bool isFlag) { flag = isFlag; }
            void setNumber(const int isNumber) { number = isNumber; }

            void reset() {
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

    class Board
    {
        public:
            Board();
            ~Board() = default;

            static constexpr std::size_t SIZE_ARRAY_ROW = 16;
            static constexpr std::size_t SIZE_ARRAY_CELL = 30;

            std::array<std::array<Cell, SIZE_ARRAY_CELL>, SIZE_ARRAY_ROW>& getMap() { return _map; }            bool verifMapIsEmpty();
            void initializeMap();
            void placeMine();
            int conditionAdjBomb(const ANAL::Vector2<int>& coords);
            void adjacentBombs();
            

            Cell& getCell(const ANAL::Vector2<int>& coords);

            std::vector<std::string> mapToDisplay();

            void mapVisible();
            void toVisible(const ANAL::Vector2<int>& coords);

        private:
            std::array<std::array<Cell, SIZE_ARRAY_CELL>, SIZE_ARRAY_ROW> _map = {};
    };

    class Minesweeper final : public ANAL::IGame
    {
        public:
            enum STATE {
                RESTARTING,
                RUNNING,
                DEFEAT,
                WIN,
            };
            Minesweeper() { this->init(); }
            ~Minesweeper() override = default;
            
            void processEvents(std::vector<ANAL::Event>&) override;
            void compute(ANAL::IArcade& arcade) override;
            void render(ANAL::IRenderer& renderer, const ANAL::IArcade& arcade) override;

            [[nodiscard]] STATE getState() const { return this->_state; }
            void setState(const STATE state) { this->_state = state; }

            static constexpr std::size_t NUMBER_OF_BOMBS = 50;

        private:
            void init();
            void restart() { this->init(); }

            Board _board;
            STATE _state{};
            std::vector<std::string> _currentMap = {};
	        std::string _playername{};
            ANAL::Vector2<int> _lastClickPos{0, 0};
            int _bestScore{};
            bool _firstClick = true;
            int _bombFlagged{};
            int _flags = NUMBER_OF_BOMBS;
            std::size_t _frame{};
    };
} // namespace Minesweeper

#endif // MINESWEEPER_HPP
