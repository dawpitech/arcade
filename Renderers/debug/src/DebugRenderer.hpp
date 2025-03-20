/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** DebugRenderer.hpp
*/

#ifndef DEBUGRENDERER_HPP
    #define DEBUGRENDERER_HPP

    #include "ANAL/IRenderer.hpp"

class DebugRenderer final : public anal::IRenderer
{
    public:
        DebugRenderer() = default;
        ~DebugRenderer() override = default;

        ModuleType getModuleType() override { return ModuleType::RENDERER; }
        ModuleVersion getModuleVersion() override { return ModuleVersion::V1_0_0; }

        void drawSprite(const anal::ISprite& sprite) override;
        void drawText(const std::string&, anal::Vector2<int>) override;
        void setWindowTitle(const std::string&) override;
        void render() override;
        std::vector<anal::Event>& getEvents() override;
        void clear() override;

    private:
        std::vector<anal::Event> _events;
};
#endif //DEBUGRENDERER_HPP
