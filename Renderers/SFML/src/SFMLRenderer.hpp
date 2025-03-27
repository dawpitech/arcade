/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** SFMLRenderer.hpp
*/

#ifndef SFMLRENDERER_HPP
    #define SFMLRENDERER_HPP

    #include <ANAL/IRenderer.hpp>

namespace arcade
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
    };
}


#endif //SFMLRENDERER_HPP
