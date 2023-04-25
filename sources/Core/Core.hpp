//
// Created by Clément Lagasse on 24/04/2023.
//

#ifndef MY_RAYTRACER_CORE_HPP
#define MY_RAYTRACER_CORE_HPP

class SceneManager;
class PluginFactory;
class GraphModule;
class Image;

namespace RayTracer {
    namespace Core {

        class Core {
        public:
            Core(const std::string &configDir, const std::string &pluginDir);
            ~Core();

            void run();
        private:
            void handleEvents();
            PluginFactory pluginFactory;
            SceneManager sceneManager;
            GraphModule *graphModule;
            Image image;
        };

    } // RayTracer
} // Core

#endif //MY_RAYTRACER_CORE_HPP
