/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** NCURSESRenderer.hpp
*/

#ifndef NCURSESRENDERER_HPP
    #define NCURSESRENDERER_HPP

    #include <ANAL/IRenderer.hpp>
    #include <fstream>
    #include <map>
    #include <ncurses.h>

namespace arcade::renderers
{
    class NCursesRenderer final : public ANAL::IRenderer
    {
        public:
            NCursesRenderer();
            ~NCursesRenderer() override;

            void drawEntity(const ANAL::IEntity& entity) override;
            void drawText(const std::string&, ANAL::Vector2<int>) override;

            void setWindowTitle(const std::string&) override;

            void render() override;
            void clear() override;

            std::vector<ANAL::Event>& getEvents() override;

        private:
            WINDOW* _window;
            std::streambuf* _backupbuffer;
            std::ofstream _nullstream{"/dev/null"};
            std::vector<ANAL::Event> _events;
            SCREEN* _screen;
            std::vector<std::pair<mmask_t, ANAL::MouseKeys>> MOUSEBINDS_LIST = {
                {BUTTON1_PRESSED, ANAL::MouseKeys::LEFT_CLICK},
                {BUTTON1_RELEASED, ANAL::MouseKeys::LEFT_CLICK},
                {BUTTON2_PRESSED, ANAL::MouseKeys::MIDDLE_CLICK},
                {BUTTON2_RELEASED, ANAL::MouseKeys::MIDDLE_CLICK},
                {BUTTON3_PRESSED, ANAL::MouseKeys::RIGHT_CLICK},
                {BUTTON3_RELEASED, ANAL::MouseKeys::RIGHT_CLICK},
           };
            std::map<int, ANAL::Keys> KEYBINDS_MAP = {
                {'a', ANAL::Keys::KEY_A},
                {'b', ANAL::Keys::KEY_B},
                {'c', ANAL::Keys::KEY_C},
                {'d', ANAL::Keys::KEY_D},
                {'e', ANAL::Keys::KEY_E},
                {'f', ANAL::Keys::KEY_F},
                {'g', ANAL::Keys::KEY_G},
                {'h', ANAL::Keys::KEY_H},
                {'i', ANAL::Keys::KEY_I},
                {'j', ANAL::Keys::KEY_J},
                {'k', ANAL::Keys::KEY_K},
                {'l', ANAL::Keys::KEY_L},
                {'m', ANAL::Keys::KEY_M},
                {'n', ANAL::Keys::KEY_N},
                {'o', ANAL::Keys::KEY_O},
                {'p', ANAL::Keys::KEY_P},
                {'q', ANAL::Keys::KEY_Q},
                {'r', ANAL::Keys::KEY_R},
                {'s', ANAL::Keys::KEY_S},
                {'t', ANAL::Keys::KEY_T},
                {'u', ANAL::Keys::KEY_U},
                {'v', ANAL::Keys::KEY_V},
                {'w', ANAL::Keys::KEY_W},
                {'x', ANAL::Keys::KEY_X},
                {'y', ANAL::Keys::KEY_Y},
                {'z', ANAL::Keys::KEY_Z},
                {KEY_UP, ANAL::Keys::ARROW_UP},
                {KEY_LEFT, ANAL::Keys::ARROW_LEFT},
                {KEY_RIGHT, ANAL::Keys::ARROW_RIGHT},
                {KEY_DOWN, ANAL::Keys::ARROW_DOWN},
                {' ', ANAL::Keys::SPECIAL_KEY_SPACE},
                {KEY_BACKSPACE, ANAL::Keys::SPECIAL_KEY_BACKSPACE},
                {'\n', ANAL::Keys::SPECIAL_KEY_ENTER},
            };
    };
}

#endif //NCURSESRENDERER_HPP
