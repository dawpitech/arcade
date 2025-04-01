/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** MainMenu.hpp
*/

#ifndef MAINMENU_HPP
    #define MAINMENU_HPP

    #include <ANAL/IGame.hpp>

class MainMenu final : public ANAL::IGame
{
    public:
        MainMenu() = default;
        ~MainMenu() override = default;

        void processEvents(std::vector<ANAL::Event>&) override;
        void compute() override;
        void render(ANAL::IRenderer& renderer, const ANAL::IArcade& arcade) override;
};
#endif //MAINMENU_HPP
