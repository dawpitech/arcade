/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Asset.hpp
*/

#ifndef ASSET_HPP
    #define ASSET_HPP

    #include <string>

    #include "ANAL/IAsset.hpp"

class Asset final : public ANAL::IAsset
{
    public:
        Asset() = default;
        ~Asset() override = default;

        void setTexturePath(const std::string&) override;
        [[nodiscard]] const std::string& getTexturePath() const override;

        void setAlternateRender(char) override;
        [[nodiscard]] char getAlternateRender() const override;

    private:
        std::string _texturePath;
        char _alternateRender = '?';
};
#endif //ASSET_HPP
