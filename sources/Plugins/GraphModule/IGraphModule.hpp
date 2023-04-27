/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** IGraphModule
*/

#ifndef IGRAPHMODULE_HPP_
#define IGRAPHMODULE_HPP_

#include "ISceneManager.hpp"

namespace RayTracer {
    namespace Plugins {
        class IGraphModule {
            public:
                IGraphModule();
                ~IGraphModule();

                virtual void update(RayTracer::Core::IEventManager &eventManager,
                    RayTracer::Core::Image &image) = 0;
            protected:
            private:
        };
    } // namespace Plugins
} // namespace RayTracer

#endif /* !IGRAPHMODULE_HPP_ */
