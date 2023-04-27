//
// Created by Theophilus Homawoo on 15/04/2023.
//

#ifndef RAYTRACING_CUSTOMERROR_HPP
#define RAYTRACING_CUSTOMERROR_HPP

#include <stdexcept>
#include <string>

namespace RayTracer {
    namespace Shared {
        class CustomError : public std::exception {
        public:
            explicit CustomError(const std::string &message) : message_(message) {}

            const char *what() const

            noexcept override{
                    return message_.c_str();
            }

        private:
            std::string message_;
        };
    }
}


#endif //RAYTRACING_CUSTOMERROR_HPP
