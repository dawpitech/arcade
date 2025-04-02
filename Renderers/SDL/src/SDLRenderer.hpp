/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** SDLRenderer.hpp
*/

#ifndef SDLRENDERER_HPP
    #define SDLRENDERER_HPP

    #include <SDL2/SDL.h>
    #include <ANAL/IRenderer.hpp>
    #define SCALE_FACTOR 16
    #define WINDOW_SIZE 32
    #define FONT_SIZE 1

namespace arcade
{
    class SDLRenderer final : public ANAL::IRenderer
    {
        public:
            SDLRenderer();
            ~SDLRenderer() override;

            void drawEntity(const ANAL::IEntity& entity) override;
            void drawText(const std::string&, ANAL::Vector2<int>) override;

            void setWindowTitle(const std::string&) override;

            void render() override;
            void clear() override;

            std::vector<ANAL::Event>& getEvents() override;

        private:
            SDL_Window* _window;
            SDL_Renderer* _renderer;
            std::vector<ANAL::Event> _events;
    };
}


#endif //SDLRENDERER_HPP
