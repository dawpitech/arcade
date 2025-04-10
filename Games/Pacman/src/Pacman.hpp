/*
** EPITECH PROJECT, 2025
** pacman
** File description:
** uwu
*/

#pragma once

#include "ANAL/IArcade.hpp"
#include "ANAL/IGame.hpp"
#include "ANAL/Vector2.hpp"

namespace arcade::games
{

    class Player
    {
        public:
            enum STATE
            {
                NORMAL,
                HIGH,
                DEAD
            };

            enum LOOK
            {
                RIGHT,
                LEFT
            };

            Player();

            [[nodiscard]] int getScore() const;
            void setScore(int Score);
            [[nodiscard]] ANAL::Vector2<int> getPos() const;
            void setPos(ANAL::Vector2<int> v);
            [[nodiscard]] Player::STATE getState() const;
            void setState(Player::STATE s);
            void tickHigh();
            void tickReset();
            [[nodiscard]] LOOK getLook() const;
            void setLook(LOOK);

        private:
            int m_score;
            ANAL::Vector2<int> m_player_pos{16, 18};
            Player::STATE m_state;
            int m_tick_to_normal;
            LOOK m_look;
    };

    class Ghost
    {
        public:
            enum STATE
            {
                NORMAL,
                SCARED,
                DEAD
            };

            enum LOOK
            {
                RIGHT,
                LEFT
            };

            Ghost(ANAL::Vector2<int> pos, const std::string &color);

            [[nodiscard]] ANAL::Vector2<int> getPos() const;
            [[nodiscard]] ANAL::Vector2<int> getOrgPos() const;
            void setPos(ANAL::Vector2<int> v);
            [[nodiscard]] Ghost::STATE getState() const;
            void setState(Ghost::STATE s);
            void tickDead();
            void tickReset();
            [[nodiscard]] LOOK getLook() const;
            void setLook(LOOK);
            [[nodiscard]] std::string getColor() const;
            void setColor(const std::string &col);
            [[nodiscard]] bool getPassedGate() const;
            void setPassedGate(const bool &p);

        private:
            ANAL::Vector2<int> m_ghost_pos{0, 0};
            ANAL::Vector2<int> m_ghost_org_pos{0, 0};
            STATE m_state;
            int m_tick_to_normal;
            std::string m_color;
            bool m_passed_gate;
            LOOK m_look;
    };

    class Pacman final : public ANAL::IGame
    {
        public:
            Pacman();
            ~Pacman() override;

            void processEvents(std::vector<ANAL::Event> &) override;
            void compute(ANAL::IArcade &arcade) override;
            void render(ANAL::IRenderer &renderer, const ANAL::IArcade &arcade) override;

        private:
            void deinit();
            void init();
            void restart();

            static constexpr std::size_t MAPSIZE = 32;
            std::vector<std::string> _currentMap;
            Player _player;
            std::string _playername;
            int _ghostsTime = 0;
            int _bestScore;
            std::vector<Ghost> _ghosts;
            const std::vector<std::string> MAP = {
                "                             ",
                "                             ",
                " ############################",
                " #.............o............#",
                " #............##............#",
                " #.####.#####.##.#####.####.#",
                " #.####.#####.##.#####.####.#",
                " #..........................#",
                " #..........................#",
                " #..###.##.########.##.###..#",
                " #......##....##..o.##......#",
                " #####..#####.##.#####..#####",
                "     #..##..........##..#    ",
                "     #..##.###__###.##..#    ",
                " #####..##.#      #.##..#####",
                " #.o.......#      #.........#",
                " #####..##.#      # ##..#####",
                "     #..##.######## ##..#    ",
                "     #..##..........##..#    ",
                " #####..##.########.##..#####",
                " #............##............#",
                " #..###.#####.##.#####.###..#",
                " #...##................##...#",
                " #...##................##...#",
                " ##..##.##.########.##.##..##",
                " #......##....##....##......#",
                " #.##########.##.##########.#",
                " #..........................#",
                " #.............o............#",
                " ############################",
                "                             ",
                "                             "
            };
    };

} // namespace arcade::games
