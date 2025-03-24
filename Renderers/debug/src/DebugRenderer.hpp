/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** DebugRenderer.hpp
*/

#ifndef DEBUGRENDERER_HPP
    #define DEBUGRENDERER_HPP

    #include "ANAL/IRenderer.hpp"

class DebugRenderer final : public ANAL::IRenderer
{
    public:
        DebugRenderer() = default;
        ~DebugRenderer() override {
            std::cout << "[DEBUG] Renderer destroyed" << std::endl;
        }

        void drawSprite(const ANAL::ISprite& sprite) override;
        void drawText(const std::string&, ANAL::Vector2<int>) override;
        void setWindowTitle(const std::string&) override;
        void render() override;
        std::vector<ANAL::Event>& getEvents() override;
        void clear() override;

    private:
        std::vector<ANAL::Event> _events;
};
#endif //DEBUGRENDERER_HPP
