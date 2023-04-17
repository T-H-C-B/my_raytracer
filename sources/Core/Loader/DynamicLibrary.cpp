//
// Created by Theophilus Homawoo on 16/04/2023.
//

#include "DynamicLibrary.hpp"

DynamicLibrary::DynamicLibrary(const std::string &filename) : handle(nullptr) {
    handle = dlopen(filename.c_str(), RTLD_NOW);
    if (!handle) {
        throw std::runtime_error("Failed to open dynamic library: " + std::string(dlerror()));
    }
}

DynamicLibrary::~DynamicLibrary() {
    if (handle) {
        dlclose(handle);
    }
}

