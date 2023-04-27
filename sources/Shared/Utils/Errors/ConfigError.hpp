//
// Created by Theophilus Homawoo on 15/04/2023.
//

#ifndef RAYTRACING_CONFIGERROR_HPP
#define RAYTRACING_CONFIGERROR_HPP

#include "CustomError.hpp"

namespace RayTracer {
    namespace Shared {
        class ConfigError : public CustomError {
        public:
            explicit ConfigError(const std::string &type)
            : CustomError("ConfigError: " + type) {}

            explicit ConfigError(const std::string &type, const std::string &name)
            : CustomError("ConfigError: " + type + " " + name) {};
        };
    }
}

#endif //RAYTRACING_CONFIGERROR_HPP
