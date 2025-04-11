/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** SDLRenderer.hpp
*/

#ifndef SDLRENDERER_HPP
    #define SDLRENDERER_HPP

    #include <map>
    #include <SDL2/SDL.h>

    #include "ANAL/IRenderer.hpp"

#include <SFML/Window/Keyboard.hpp>

#define SCALE_FACTOR 16
    #define WINDOW_SIZE 32
    #define FONT_SIZE 1

namespace arcade::renderers
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
            std::map<Uint8, ANAL::MouseKeys> MOUSEBINDS_MAP = {
                {SDL_BUTTON_LEFT, ANAL::MouseKeys::LEFT_CLICK},
                {SDL_BUTTON_MIDDLE, ANAL::MouseKeys::MIDDLE_CLICK},
                {SDL_BUTTON_RIGHT, ANAL::MouseKeys::RIGHT_CLICK},
            };
            std::map<SDL_Keycode, ANAL::Keys> KEYBINDS_MAP = {
                {SDLK_a, ANAL::Keys::KEY_A},
                {SDLK_b, ANAL::Keys::KEY_B},
                {SDLK_c, ANAL::Keys::KEY_C},
                {SDLK_d, ANAL::Keys::KEY_D},
                {SDLK_e, ANAL::Keys::KEY_E},
                {SDLK_f, ANAL::Keys::KEY_F},
                {SDLK_g, ANAL::Keys::KEY_G},
                {SDLK_h, ANAL::Keys::KEY_H},
                {SDLK_i, ANAL::Keys::KEY_I},
                {SDLK_j, ANAL::Keys::KEY_J},
                {SDLK_k, ANAL::Keys::KEY_K},
                {SDLK_l, ANAL::Keys::KEY_L},
                {SDLK_m, ANAL::Keys::KEY_M},
                {SDLK_n, ANAL::Keys::KEY_N},
                {SDLK_o, ANAL::Keys::KEY_O},
                {SDLK_p, ANAL::Keys::KEY_P},
                {SDLK_q, ANAL::Keys::KEY_Q},
                {SDLK_r, ANAL::Keys::KEY_R},
                {SDLK_s, ANAL::Keys::KEY_S},
                {SDLK_t, ANAL::Keys::KEY_T},
                {SDLK_u, ANAL::Keys::KEY_U},
                {SDLK_v, ANAL::Keys::KEY_V},
                {SDLK_w, ANAL::Keys::KEY_W},
                {SDLK_x, ANAL::Keys::KEY_X},
                {SDLK_y, ANAL::Keys::KEY_Y},
                {SDLK_z, ANAL::Keys::KEY_Z},
                {SDLK_0, ANAL::Keys::KEY_0},
                {SDLK_1, ANAL::Keys::KEY_1},
                {SDLK_2, ANAL::Keys::KEY_2},
                {SDLK_3, ANAL::Keys::KEY_3},
                {SDLK_4, ANAL::Keys::KEY_4},
                {SDLK_5, ANAL::Keys::KEY_5},
                {SDLK_6, ANAL::Keys::KEY_6},
                {SDLK_7, ANAL::Keys::KEY_7},
                {SDLK_8, ANAL::Keys::KEY_8},
                {SDLK_9, ANAL::Keys::KEY_9},
                {SDLK_UP, ANAL::Keys::ARROW_UP},
                {SDLK_LEFT, ANAL::Keys::ARROW_LEFT},
                {SDLK_RIGHT, ANAL::Keys::ARROW_RIGHT},
                {SDLK_DOWN, ANAL::Keys::ARROW_DOWN},
                {SDLK_SPACE, ANAL::Keys::SPECIAL_KEY_SPACE},
                {SDLK_BACKSPACE, ANAL::Keys::SPECIAL_KEY_BACKSPACE},
                {SDLK_RETURN, ANAL::Keys::SPECIAL_KEY_ENTER},
            };
    };
}


#endif //SDLRENDERER_HPP
