/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** NCURSESRenderer.hpp
*/

#ifndef NCURSESRENDERER_HPP
    #define NCURSESRENDERER_HPP

    #include <ncurses.h>
    #include <ANAL/IRenderer.hpp>
    #include <fstream>

namespace arcade
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
    };
}

#endif //NCURSESRENDERER_HPP
