/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** Arcade.hpp
*/

#ifndef MINESWEEPER_HPP
    #define MINESWEEPER_HPP

    #define EXIT_FAILURE_TECH 84

    #include <iostream>
    #include <algorithm>
    #include <vector>
    #include <string>
    #include <ANAL/IGame.hpp>
    #include <ANAL/IRenderer.hpp>

namespace Pacman
{
    class Ghosts : public Game
    {
        public:
            Ghosts();
            ~Ghosts() = default;

        private:
            struct positionGhosts {
                int x;
                int y;
            };
            positionGhosts _player;
            int direction;
    };
    class Player : public Game
    {
        public:
            Player();
            ~Player() = default;
            const std::vector<std::string>& getMap();
            std::vector<std::string> setMap();
            void initializeMap();
            void clearMap();
        private:
            struct positionPlayer {
                int x;
                int y;
            };
            positionPlayer _player;
            int _direction;
            std::vector<std::string> _map;
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
            int _score;
            int _maxscore;
            bool _restart = false;
    };
}

#endif //MINESWEEPER_HPP
