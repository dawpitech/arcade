/*
** EPITECH PROJECT, 2025
** Snake
** File description:
** uwu
*/

#pragma once

#include <deque>

#include "ANAL/IGame.hpp"
#include "ANAL/Vector2.hpp"

namespace arcade::games
{
    class Snake final : public ANAL::IGame
    {
        public:
            Snake(): _rng(_rd()) { this->init(); }
            ~Snake() override = default;

            void processEvents(std::vector<ANAL::Event> &) override;
            void compute(ANAL::IArcade &arcade) override;
            void render(ANAL::IRenderer &renderer, const ANAL::IArcade &arcade) override;

        private:
            void init();
            void restart() { this->init(); }

            std::vector<std::string> _currentMap;
            ANAL::Vector2<int> _berryPos{0, 0};
            std::deque<ANAL::Vector2<int>> _snake;
            ANAL::Vector2<int> _direction{0, 0};
            std::string _playerName;
            bool _gameEnded{};
            int _score{};
            int _bestScore{};

            std::random_device _rd;
            std::mt19937 _rng;
            void moveBerryRandom();

            const std::vector<std::string> MAP = {
                ".............................",
                ".............................",
                "##############################",
                "#                            #",
                "#                            #",
                "#                            #",
                "#                            #",
                "#                            #",
                "#                            #",
                "#                            #",
                "#                            #",
                "#                            #",
                "#                            #",
                "#                            #",
                "#                            #",
                "#                            #",
                "#                            #",
                "#                            #",
                "#                            #",
                "#                            #",
                "#                            #",
                "#                            #",
                "#                            #",
                "#                            #",
                "#                            #",
                "#                            #",
                "#                            #",
                "#                            #",
                "#                            #",
                "#                            #",
                "##############################",
                ".............................",
            };
    };
} // namespace arcade::games
