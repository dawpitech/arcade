/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** Arcade.hpp
*/

#ifndef ARCADE_HPP
    #define ARCADE_HPP

    #define EXIT_FAILURE_TECH 84

    #include "ANAL/IGame.hpp"
    #include "ANAL/IRenderer.hpp"
    #include "utils/SafeDL.hpp"

class Arcade final : public ANAL::IArcade
{
    public:
        Arcade() = default;
        ~Arcade() override
        {
            this->_renderer.reset();
            this->_game.reset();
            this->_renderer_so_handle.reset();
            this->_game_so_handle.reset();
        }

        static void printHelp();
        void launch();

        void setGame(std::unique_ptr<ANAL::IGame>&);
        void setRenderer(std::unique_ptr<ANAL::IRenderer>&);

        [[nodiscard]] std::unique_ptr<ANAL::IAsset> newAsset() const override;
        [[nodiscard]] std::unique_ptr<ANAL::IEntity> newEntity() const override;

        SafeDL::safeHandle _game_so_handle;
        SafeDL::safeHandle _renderer_so_handle;

    private:
        std::unique_ptr<ANAL::IGame> _game;
        std::unique_ptr<ANAL::IRenderer> _renderer;
        bool run = true;
};
#endif //ARCADE_HPP
