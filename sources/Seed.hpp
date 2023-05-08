//
// Created by Theophilus Homawoo on 08/05/2023.
//

#pragma once

class Seed {
public:
    static Seed& getInstance() {
        static Seed instance;
        return instance;
    }

    unsigned int get() const {
        return seedValue;
    }

    void set(unsigned int value) {
        seedValue = value;
    }

private:
    Seed() = default;
    ~Seed() = default;

    Seed(const Seed&) = delete;
    Seed& operator=(const Seed&) = delete;

    unsigned int seedValue;
};

