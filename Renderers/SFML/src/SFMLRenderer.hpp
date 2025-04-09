/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** SFMLRenderer.hpp
*/

#ifndef SFMLRENDERER_HPP
    #define SFMLRENDERER_HPP

    #include <ANAL/IRenderer.hpp>

    #define SCALE_FACTOR 16
    #define WINDOW_SIZE 32
    #define FONT_SIZE 1

namespace arcade::renderers
{
    class SFMLRenderer final : public ANAL::IRenderer
    {
        public:
            SFMLRenderer();
            ~SFMLRenderer() override;

            void drawEntity(const ANAL::IEntity& entity) override;
            void drawText(const std::string&, ANAL::Vector2<int>) override;

            void setWindowTitle(const std::string&) override;

            void render() override;
            void clear() override;

            std::vector<ANAL::Event>& getEvents() override;

        private:
            sf::RenderWindow _window;
            std::vector<ANAL::Event> _events;
            std::map<sf::Mouse::Button, ANAL::MouseKeys> MOUSEBINDS_MAP = {
                {sf::Mouse::Button::Left, ANAL::MouseKeys::LEFT_CLICK},
                {sf::Mouse::Button::Middle, ANAL::MouseKeys::MIDDLE_CLICK},
                {sf::Mouse::Button::Right, ANAL::MouseKeys::RIGHT_CLICK},
            };
            std::map<sf::Keyboard::Key, ANAL::Keys> KEYBINDS_MAP = {
                {sf::Keyboard::A, ANAL::Keys::KEY_A},
                {sf::Keyboard::B, ANAL::Keys::KEY_B},
                {sf::Keyboard::C, ANAL::Keys::KEY_C},
                {sf::Keyboard::D, ANAL::Keys::KEY_D},
                {sf::Keyboard::E, ANAL::Keys::KEY_E},
                {sf::Keyboard::F, ANAL::Keys::KEY_F},
                {sf::Keyboard::G, ANAL::Keys::KEY_G},
                {sf::Keyboard::H, ANAL::Keys::KEY_H},
                {sf::Keyboard::I, ANAL::Keys::KEY_I},
                {sf::Keyboard::J, ANAL::Keys::KEY_J},
                {sf::Keyboard::K, ANAL::Keys::KEY_K},
                {sf::Keyboard::L, ANAL::Keys::KEY_L},
                {sf::Keyboard::M, ANAL::Keys::KEY_M},
                {sf::Keyboard::N, ANAL::Keys::KEY_N},
                {sf::Keyboard::O, ANAL::Keys::KEY_O},
                {sf::Keyboard::P, ANAL::Keys::KEY_P},
                {sf::Keyboard::Q, ANAL::Keys::KEY_Q},
                {sf::Keyboard::R, ANAL::Keys::KEY_R},
                {sf::Keyboard::S, ANAL::Keys::KEY_S},
                {sf::Keyboard::T, ANAL::Keys::KEY_T},
                {sf::Keyboard::U, ANAL::Keys::KEY_U},
                {sf::Keyboard::V, ANAL::Keys::KEY_V},
                {sf::Keyboard::W, ANAL::Keys::KEY_W},
                {sf::Keyboard::X, ANAL::Keys::KEY_X},
                {sf::Keyboard::Y, ANAL::Keys::KEY_Y},
                {sf::Keyboard::Z, ANAL::Keys::KEY_Z},
                {sf::Keyboard::Num0, ANAL::Keys::KEY_0},
                {sf::Keyboard::Num1, ANAL::Keys::KEY_1},
                {sf::Keyboard::Num2, ANAL::Keys::KEY_2},
                {sf::Keyboard::Num3, ANAL::Keys::KEY_3},
                {sf::Keyboard::Num4, ANAL::Keys::KEY_4},
                {sf::Keyboard::Num5, ANAL::Keys::KEY_5},
                {sf::Keyboard::Num6, ANAL::Keys::KEY_6},
                {sf::Keyboard::Num7, ANAL::Keys::KEY_7},
                {sf::Keyboard::Num8, ANAL::Keys::KEY_8},
                {sf::Keyboard::Num9, ANAL::Keys::KEY_9},
                {sf::Keyboard::Up, ANAL::Keys::ARROW_UP},
                {sf::Keyboard::Left, ANAL::Keys::ARROW_LEFT},
                {sf::Keyboard::Right, ANAL::Keys::ARROW_RIGHT},
                {sf::Keyboard::Down, ANAL::Keys::ARROW_DOWN},
            };
    };
}


#endif //SFMLRENDERER_HPP
