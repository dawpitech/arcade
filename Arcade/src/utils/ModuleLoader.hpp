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

        static std::unique_ptr<anal::IModule> loadModule(const SafeDL::safeHandle& handle)
        {
            const auto func = reinterpret_cast<std::unique_ptr<anal::IModule>(*)()>
                (dlsym(handle.get(), "uwu_entrypoint_module"));
            if (func == nullptr)
                throw Exception("Shared library is not a compatible ANAL module");
            auto module = func();
            if (module->getModuleVersion() >= anal::IModule::ModuleVersion::NOT_SUPPORTED)
                throw Exception("ANAL module is not using a supported version");
            if (module->getModuleType() == anal::IModule::ModuleType::UNKNOWN)
                throw Exception("ANAL module type unknown");
            return std::move(module);
        }
};
#endif //MODULELOADER_HPP
