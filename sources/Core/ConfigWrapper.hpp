//
// Created by Bartosz on 5/5/23.
//

#pragma once
#include <libconfig.h++>
#include <string>


namespace RayTracer {
    namespace Core {
            class ConfigWrapper {
            public:
                ConfigWrapper();

                bool readFile(const std::string &filename);
                bool writeToFile(const std::string &filename);

                template <typename T>
                bool lookup(const std::string &path, T &value);

            private:
                libconfig::Config cfg;
            };
    } // RayTracer
} // Core

