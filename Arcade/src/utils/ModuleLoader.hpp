/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** ModuleLoader.hpp
*/

#ifndef MODULELOADER_HPP
    #define MODULELOADER_HPP

    #include "SafeDL.hpp"
    #include "ANAL/IModule.hpp"

class ModuleLoader
{
    public:
        class Exception final : public std::exception
        {
            public:
                explicit Exception(const std::string& what = "ModuleLoader Exception") { this->_what = what; }
                [[nodiscard]] const char* what() const noexcept override { return this->_what.c_str(); }

            private:
                std::string _what;
        };

        static ANAL::ModuleType getModuleType(const SafeDL::safeHandle& handle)
        {
            const auto func = reinterpret_cast<ANAL::ModuleType(*)()>
                (dlsym(handle.get(), "uwu_get_module_type"));
            if (func == nullptr)
                throw Exception("Couldn't retrieve module info from shared library");
            return func();
        }

        static ANAL::ModuleVersion getModuleVersion(const SafeDL::safeHandle& handle)
        {
            const auto func = reinterpret_cast<ANAL::ModuleVersion(*)()>
                (dlsym(handle.get(), "uwu_get_module_version"));
            if (func == nullptr)
                throw Exception("Couldn't retrieve module info from shared library");
            return func();
        }

        static std::unique_ptr<ANAL::IGame> loadGame(const SafeDL::safeHandle& handle)
        {
            const auto func = reinterpret_cast<std::unique_ptr<ANAL::IGame>(*)()>
                (dlsym(handle.get(), "uwu_entrypoint_game"));
            if (func == nullptr)
                throw Exception("Couldn't retrieve game from shared library");
            auto game = func();
            return std::move(game);
        }

        static std::unique_ptr<ANAL::IRenderer> loadRenderer(const SafeDL::safeHandle& handle)
        {
            const auto func = reinterpret_cast<std::unique_ptr<ANAL::IRenderer>(*)()>
                (dlsym(handle.get(), "uwu_entrypoint_renderer"));
            if (func == nullptr)
                throw Exception("Couldn't retrieve renderer from shared library");
            auto renderer = func();
            return std::move(renderer);

        }
};
#endif //MODULELOADER_HPP
