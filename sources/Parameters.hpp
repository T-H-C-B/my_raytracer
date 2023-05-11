//
// Created by Theophilus Homawoo on 08/05/2023.
//

#pragma once

class Parameters {
public:
    static Parameters& getInstance() {
        static Parameters instance;
        return instance;
    }

    unsigned int getSeed() const {
        return seedValue;
    }

    void setSeed(unsigned int value) {
        seedValue = value;
    }

    unsigned int getNumOcclusionRays() const {
        return numOcclusionRays;
    }

    void setNumOcclusionRays(unsigned int value) {
        numOcclusionRays = value;
    }

    unsigned int getNumShadowRays() const {
        return numShadowRays;
    }

    void setNumShadowRays(unsigned int value) {
        numShadowRays = value;
    }

private:
    Parameters() = default;
    ~Parameters() = default;

    Parameters(const Parameters&) = delete;
    Parameters& operator=(const Parameters&) = delete;

    unsigned int seedValue;
    unsigned int numOcclusionRays;
    unsigned int numShadowRays;
};

