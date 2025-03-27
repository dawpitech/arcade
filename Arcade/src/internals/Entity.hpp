/*
** EPITECH PROJECT, 2025
** Arcade
** File description:
** Entity.hpp
*/

#ifndef ENTITY_HPP
    #define ENTITY_HPP

    #include <memory>

    #include "Asset.hpp"
    #include "ANAL/IAsset.hpp"
    #include "ANAL/IEntity.hpp"
    #include "ANAL/Vector2.hpp"

class Entity final : public ANAL::IEntity
{
    public:
        Entity() = default;
        ~Entity() override = default;

        [[nodiscard]] const ANAL::IAsset& getAsset() const override;
        void setAsset(const ANAL::IAsset&) override;

        [[nodiscard]] const ANAL::Vector2<int>& getPos() const override;
        void setPos(const ANAL::Vector2<int>&) override;

    private:
        std::unique_ptr<ANAL::IAsset> _asset;
        ANAL::Vector2<int> _pos{0, 0};
};
#endif //ENTITY_HPP
