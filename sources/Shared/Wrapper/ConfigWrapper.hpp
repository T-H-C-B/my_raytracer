//
// Created by Bartosz on 5/5/23.
//

#pragma once
#include <string>
#include "SettingWrapper.hpp"


namespace RayTracer {
    namespace Shared {

            class FileIOException : public std::exception {
            public:
                FileIOException(const std::string& message) : msg(message) {}
                const char* what() const noexcept override { return msg.c_str(); }
            private:
                std::string msg;
            };

            class ParseException : public std::exception {
            public:
                ParseException(const std::string& message) : msg(message) {}
                const char* what() const noexcept override { return msg.c_str(); }
            private:
                std::string msg;
            };
            class ConfigWrapper {
            public:
                ConfigWrapper();

                bool readFile(const std::string &filename);
                bool writeToFile(const std::string &filename);
                SettingWrapper getRoot() const;

                template <typename T>
                bool lookup(const std::string &path, T &value);

            private:
                libconfig::Config cfg;
            };
    } // RayTracer
} // Core

