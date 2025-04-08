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
        void scanForModules();
        void handleHotKeys(std::vector<ANAL::Event>&);

        void setGame(std::unique_ptr<ANAL::IGame>&);
        void setRenderer(std::unique_ptr<ANAL::IRenderer>&);

        void addToGameList(const std::string&);
        void addToRendererList(const std::string&);

        [[nodiscard]] std::unique_ptr<ANAL::IAsset> newAsset() const override;
        [[nodiscard]] std::unique_ptr<ANAL::IEntity> newEntity() const override;

        [[nodiscard]] const std::vector<std::string>& getGamesList() const;
        void launchGame(int idx);

        SafeDL::safeHandle _game_so_handle;
        SafeDL::safeHandle _renderer_so_handle;

    private:
        std::unique_ptr<ANAL::IGame> _game;
        std::unique_ptr<ANAL::IRenderer> _renderer;
        std::vector<std::string> _games;
        std::size_t _game_idx = 0;
        std::vector<std::string> _renderers;
        std::size_t _renderer_idx = 0;
        bool run = true;

        static bool str_ends_with(const std::string&, const std::string&);
};
#endif //ARCADE_HPP
