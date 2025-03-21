/*
** EPITECH PROJECT, 2025
** arcade
** File description:
** SafeDL.hpp
*/

#ifndef SAFEDL_HPP
    #define SAFEDL_HPP

    #include <dlfcn.h>
    #include <exception>
    #include <memory>

class SafeDL
{
    public:
        class Exception final : public std::exception
        {
            public:
                [[nodiscard]] const char* what() const noexcept override { return "Couldn't open given shared library"; }
        };

        struct SafeDLDeleter
        {
            void operator()(void* handle) const
            {
                if (handle == nullptr || dlclose(handle) != 0)
                    throw Exception();
            }
        };
        typedef std::unique_ptr<void, SafeDLDeleter> safeHandle;

        static safeHandle make_safeHandle(void* handle) { return safeHandle(handle); }

        static safeHandle open(const std::string& filename, const int flags)
        {
            const std::string filename_r = "./" + filename;
            void* rawHandle = dlopen(filename_r.c_str(), flags);
            if (rawHandle == nullptr)
                throw Exception();
            return make_safeHandle(rawHandle);
        }
};
#endif //SAFEDL_HPP
