/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** MainMenu.hpp
*/

#ifndef MAINMENU_HPP
    #define MAINMENU_HPP

    #include <ANAL/IGame.hpp>

class MainMenu final : public anal::IGame
{
    public:
        MainMenu() = default;
        ~MainMenu() override = default;

        ModuleType getModuleType() override { return ModuleType::GAME; }
        ModuleVersion getModuleVersion() override { return ModuleVersion::V1_0_0; }

        void processEvents(const std::vector<anal::Event>&) override;
        void compute() override;
        void render() override;
};
#endif //MAINMENU_HPP
