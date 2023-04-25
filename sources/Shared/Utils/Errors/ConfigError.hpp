//
// Created by Theophilus Homawoo on 15/04/2023.
//

#ifndef RAYTRACING_CONFIGERROR_HPP
#define RAYTRACING_CONFIGERROR_HPP

#pragma once

#include "CustomError.hpp"

namespace RayTracer {
    class ConfigError : public CustomError {
    public:
        explicit ConfigError(const std::string& type);
        explicit ConfigError(const std::string& type, const std::string& name);
    };
}

#endif //RAYTRACING_CONFIGERROR_HPP
