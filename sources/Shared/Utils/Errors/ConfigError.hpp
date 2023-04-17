//
// Created by Theophilus Homawoo on 15/04/2023.
//

#ifndef RAYTRACING_CONFIGERROR_HPP
#define RAYTRACING_CONFIGERROR_HPP

#pragma once

#include "CustomError.hpp"

class ConfigError : public CustomError {
public:
    explicit ConfigError(const std::string& type) : CustomError("Config error while trying to load type: " + type) {}
    explicit ConfigError(const std::string& type, const std::string& name) : CustomError("Config error while trying to load type: " + type + " with name: " + name) {}
};

#endif //RAYTRACING_CONFIGERROR_HPP
