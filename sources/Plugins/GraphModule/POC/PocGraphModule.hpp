/*
** EPITECH PROJECT, 2023
** raytracer
** File description:
** PocGraphModule
*/

#ifndef POCGRAPHMODULE_HPP_
#define POCGRAPHMODULE_HPP_

#include "IGraphModule.hpp"

namespace RayTracer {
    namespace Plugins {
        class PocGraphModule : public IGraphModule {
            public:
                PocGraphModule();
                ~PocGraphModule() override;

                void update(RayTracer::Core::IEventManager &eventManager,
                    RayTracer::Shared::Image &image) override;
            protected:
            private:
        };
    } // namespace Plugins
} // namespace RayTracer

#endif /* !POCGRAPHMODULE_HPP_ */
