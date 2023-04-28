//
// Created by Clément Lagasse on 24/04/2023.
//

#include "Core.hpp"

RayTracer::Core::Core::Core(const std::string &graphModuleName, const std::string &configDir, const std::string &pluginDir)
: _configDir(configDir), _pluginDir(pluginDir), image(1920, 1080), _isRunning(true), _imageUpdated(true)
{
    //_GraphModule = Factory.create(graphModuleName);
}

int RayTracer::Core::Core::run()
{
    while (_isRunning) {
        handleEvents();
        if (_imageUpdated) {
            //image.render(SceneManager);
            _imageUpdated = false;
        }
        if (_graphModule != nullptr)
            _graphModule->update(_eventManager, image);
    }
    if (_catchErrors)
        return 84;
    return 0;
}

void RayTracer::Core::Core::handleEvents()
{
    static const std::unordered_map<RayTracer::Core::EventType, void (RayTracer::Core::Core::*)()> METHOD_MAP = {
            {RayTracer::Core::EventType::QUIT, &RayTracer::Core::Core::quitCore},
            {RayTracer::Core::EventType::KEY_Z_PRESSED, &RayTracer::Core::Core::goForward},
            {RayTracer::Core::EventType::KEY_S_PRESSED, &RayTracer::Core::Core::goBackward},
            {RayTracer::Core::EventType::KEY_Q_PRESSED, &RayTracer::Core::Core::goLeft},
            {RayTracer::Core::EventType::KEY_D_PRESSED, &RayTracer::Core::Core::goRight},
            {RayTracer::Core::EventType::KEY_SPACE_PRESSED, &RayTracer::Core::Core::goUp},
            {RayTracer::Core::EventType::KEY_SHIFT_PRESSED, &RayTracer::Core::Core::goDown},
            {RayTracer::Core::EventType::KEY_LEFT_PRESSED, &RayTracer::Core::Core::lookLeft},
            {RayTracer::Core::EventType::KEY_RIGHT_PRESSED, &RayTracer::Core::Core::lookRight},
            {RayTracer::Core::EventType::KEY_UP_PRESSED, &RayTracer::Core::Core::lookUp},
            {RayTracer::Core::EventType::KEY_DOWN_PRESSED, &RayTracer::Core::Core::lookDown},
            {RayTracer::Core::EventType::KEY_F1_PRESSED, &RayTracer::Core::Core::goNextScene},
            {RayTracer::Core::EventType::KEY_F2_PRESSED, &RayTracer::Core::Core::goPreviousScene},
            {RayTracer::Core::EventType::KEY_F3_PRESSED, &RayTracer::Core::Core::goNextCamera},
            {RayTracer::Core::EventType::KEY_F4_PRESSED, &RayTracer::Core::Core::goPreviousCamera},

    };
    for (auto &event : METHOD_MAP) {
        if (_eventManager.isEventTriggered(event.first)) {
            (this->*event.second)();
        }
    }
}

void RayTracer::Core::Core::quitCore()
{
    _isRunning = false;
}

void RayTracer::Core::Core::goForward()
{
    //RayTracer::Plugins::Cameras::ICamera *camera = Scene.getCamera();
    //camera.translate(Vec3(1, 0, 0));
    _imageUpdated = true;
}

void RayTracer::Core::Core::goBackward()
{
    //RayTracer::Plugins::Cameras::ICamera *camera = Scene.getCamera();
    //camera.translate(Vec3(-1, 0, 0));
    _imageUpdated = true;
}

void RayTracer::Core::Core::goLeft()
{
    //RayTracer::Plugins::Cameras::ICamera *camera = Scene.getCamera();
    //camera.translate(Vec3(0, 1, 0));
    _imageUpdated = true;
}

void RayTracer::Core::Core::goRight()
{
    //RayTracer::Plugins::Cameras::ICamera *camera = Scene.getCamera();
    //camera.translate(Vec3(0, -1, 0));
    _imageUpdated = true;
}

void RayTracer::Core::Core::goUp()
{
    //RayTracer::Plugins::Cameras::ICamera *camera = Scene.getCamera();
    //camera.translate(Vec3(0, 0, 1));
    _imageUpdated = true;
}

void RayTracer::Core::Core::goDown()
{
    //RayTracer::Plugins::Cameras::ICamera *camera = Scene.getCamera();
    //camera.translate(Vec3(0, 0, -1));
    _imageUpdated = true;
}

void RayTracer::Core::Core::lookLeft()
{
    //RayTracer::Plugins::Cameras::ICamera *camera = Scene.getCamera();
    //camera.rotate(Vec3(0, 1, 0));
    _imageUpdated = true;
}

void RayTracer::Core::Core::lookRight()
{
    //RayTracer::Plugins::Cameras::ICamera *camera = Scene.getCamera();
    //camera.rotate(Vec3(0, -1, 0));
    _imageUpdated = true;
}

void RayTracer::Core::Core::lookUp()
{
    //RayTracer::Plugins::Cameras::ICamera *camera = Scene.getCamera();
    //camera.rotate(Vec3(1, 0, 0));
    _imageUpdated = true;
}

void RayTracer::Core::Core::lookDown()
{
    //RayTracer::Plugins::Cameras::ICamera *camera = Scene.getCamera();
    //camera.rotate(Vec3(-1, 0, 0));
    _imageUpdated = true;
}

void RayTracer::Core::Core::goNextCamera()
{
    //Scene.nextCamera();
    _imageUpdated = true;
}

void RayTracer::Core::Core::goPreviousCamera()
{
    //Scene.previousCamera();
    _imageUpdated = true;
}

void RayTracer::Core::Core::goNextScene()
{
    //SceneManager.nextScene();
    _imageUpdated = true;
}

void RayTracer::Core::Core::goPreviousScene()
{
    //SceneManager.previousScene();
    _imageUpdated = true;
}

void RayTracer::Core::Core::setGraphModule(std::unique_ptr<RayTracer::Plugins::Graphics::IGraphModule> graphModule)
{
    _graphModule = std::move(graphModule);
}
