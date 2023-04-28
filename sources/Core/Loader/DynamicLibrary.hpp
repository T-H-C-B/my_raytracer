//
// Created by Theophilus Homawoo on 16/04/2023.
//

#ifndef RAYTRACING_DYNAMICLIBRARY_HPP
#define RAYTRACING_DYNAMICLIBRARY_HPP

#include <stdexcept>
#include <string>
#include <dlfcn.h>


namespace RayTracer::Core {
        class DynamicLibrary {
        public:
            explicit DynamicLibrary(const std::string &filename);

            ~DynamicLibrary();

            template<typename T>
            T getSymbol(const std::string &symbolName) {
                dlerror(); // Clear any existing error
                T symbol = reinterpret_cast<T>(dlsym(handle, symbolName.c_str()));
                const char *error = dlerror();
                if (error) {
                    throw std::runtime_error("Failed to get symbol: " + std::string(error));
                }
                return symbol;
            }

        private:
            void *handle;
        };
    }


#endif //RAYTRACING_DYNAMICLIBRARY_HPP
