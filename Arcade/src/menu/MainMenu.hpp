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
        void compute(ANAL::IArcade& arcade) override;
        void render(ANAL::IRenderer& renderer, const ANAL::IArcade& arcade) override;

    private:
        int selected_index = 0;
        int selected_game = 0;
        int selected_renderer = 0;
        bool enter = false;
};
#endif //MAINMENU_HPP
