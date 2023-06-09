//
// Created by ClÃ©ment Lagasse on 24/04/2023.
//

#include <iostream>
#include "ICamera.hpp"
#include "ACamera.hpp"
#include "Core.hpp"
#include "SettingWrapper.hpp"
#include "ConfigWrapper.hpp"
#include "ConfigError.hpp"

RayTracer::Core::Core::Core(const std::string &graphModuleName, const std::string &configDir, const std::string &pluginDir)
        : image(1920, 1080), _isRunning(true), _catchErrors(false), _configDir(configDir), _pluginDir(pluginDir), _imageUpdated(true), _ambientLight(0.1f), _renderingPercentage(0.2) ,_entityFactory(), _decoratorFactory(), _skyBoxFactory(), _graphModule(), _eventManager(), _sceneManager(configDir), _pluginLoader(_entityFactory, _decoratorFactory, _skyBoxFactory, _graphModuleFactory)
{
    std::cout << _configDir << _pluginDir << std::endl;
    RayTracer::Shared::ConfigWrapper cfg;
    const RayTracer::Shared::SettingWrapper &root = cfg.getRoot();
    _pluginLoader.loadLibraries(_pluginDir);
    try {
        _sceneManager.getCurrentScene()->init(_pluginLoader.getFactories(), _pluginLoader.getLibraries());
    } catch (const RayTracer::Shared::ConfigError &e) {
        std::cerr << e.what() << std::endl;
        _catchErrors = true;
    } catch (const RayTracer::Shared::SettingWrapper::NotFoundException &e) {
        std::cerr << e.what() << std::endl;
        _catchErrors = true;
    }
    try {
        setGraphModule(_graphModuleFactory.create(graphModuleName, root));
    } catch (const RayTracer::Shared::CustomError &e) {
        std::cerr << e.what() << std::endl;
        _catchErrors = true;
    }
}

int RayTracer::Core::Core::run()
{
    if (_catchErrors)
        return 84;
    while (_isRunning) {
        try {
            handleEvents();
            _eventManager.clearEvents();
            if (_imageUpdated) {
                image.render(*_sceneManager.getCurrentScene(), _renderingPercentage);
                _graphModule->draw(image);
                _imageUpdated = false;
            }
            if (_graphModule != nullptr)
                _graphModule->update(_eventManager);
        } catch (const RayTracer::Shared::CustomError &e) {
            std::cerr << e.what() << std::endl;
            return 84;
        } catch (const RayTracer::Shared::SettingWrapper::NotFoundException &e) {
            std::cerr << e.what() << std::endl;
            return 84;
        } catch (const RayTracer::Shared::ConfigError &e) {
            std::cerr << e.what() << std::endl;
            return 84;
        }
    }
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
            {RayTracer::Core::EventType::KEY_M_PRESSED, &RayTracer::Core::Core::goNextScene},
            {RayTracer::Core::EventType::KEY_F1_PRESSED, &RayTracer::Core::Core::goNextScene},
            {RayTracer::Core::EventType::KEY_F2_PRESSED, &RayTracer::Core::Core::goPreviousScene},
            {RayTracer::Core::EventType::KEY_F3_PRESSED, &RayTracer::Core::Core::goNextCamera},
            {RayTracer::Core::EventType::KEY_F4_PRESSED, &RayTracer::Core::Core::goPreviousCamera},
            {RayTracer::Core::EventType::KEY_P_PRESSED, &RayTracer::Core::Core::manageRenderingPercentage},

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
    RayTracer::Core::IEntity *camera = nullptr;
    RayTracer::Plugins::Cameras::ACamera *cameraPlugin = nullptr;

    try {
        std::unique_ptr<Scene> &scene = _sceneManager.getCurrentScene();
        camera = scene->getActualCamera();
        if (camera != nullptr) {
            cameraPlugin = static_cast<RayTracer::Plugins::Cameras::ACamera *>(camera);
            camera->translate(cameraPlugin->getDirection());
            _imageUpdated = true;
        }
    } catch (const RayTracer::Shared::CustomError &e) {
        std::cerr << e.what() << std::endl;
        _catchErrors = true;
    }
}

void RayTracer::Core::Core::goBackward()
{
    RayTracer::Core::IEntity *camera = nullptr;
    RayTracer::Plugins::Cameras::ACamera *cameraPlugin = nullptr;

    try {
        std::unique_ptr<Scene> &scene = _sceneManager.getCurrentScene();
        camera = scene->getActualCamera();
        if (camera != nullptr) {
            cameraPlugin = static_cast<RayTracer::Plugins::Cameras::ACamera *>(camera);
            RayTracer::Shared::Vec3 backwardDirection = cameraPlugin->getDirection();
            camera->translate(backwardDirection);
            _imageUpdated = true;
        }
    } catch (const RayTracer::Shared::CustomError &e) {
        std::cerr << e.what() << std::endl;
        _catchErrors = true;
    }
}

void RayTracer::Core::Core::goLeft()
{
    RayTracer::Core::IEntity *camera = nullptr;
    RayTracer::Plugins::Cameras::ACamera *cameraPlugin = nullptr;

    try {
        std::unique_ptr<Scene> &scene = _sceneManager.getCurrentScene();
        camera = scene->getActualCamera();
        if (camera != nullptr) {
            RayTracer::Plugins::Cameras::ACamera *cameraPlugin = static_cast<RayTracer::Plugins::Cameras::ACamera *>(camera);
            camera->translate(cameraPlugin->getLeftVector());
            _imageUpdated = true;
        }
    } catch (const RayTracer::Shared::CustomError &e) {
        std::cerr << e.what() << std::endl;
        _catchErrors = true;
    }
}

void RayTracer::Core::Core::goRight()
{
    RayTracer::Core::IEntity *camera = nullptr;
    RayTracer::Plugins::Cameras::ACamera *cameraPlugin = nullptr;

    try {
        std::unique_ptr<Scene> &scene = _sceneManager.getCurrentScene();
        camera = scene->getActualCamera();
        if (camera != nullptr) {
            RayTracer::Plugins::Cameras::ACamera *cameraPlugin = static_cast<RayTracer::Plugins::Cameras::ACamera *>(camera);
            camera->translate(cameraPlugin->getRightVector());
            _imageUpdated = true;
            std::cout << cameraPlugin->_position.x << "/" << cameraPlugin->_position.y << "/" << cameraPlugin->_position.z << std::endl;
        }
    } catch (const RayTracer::Shared::CustomError &e) {
        std::cerr << e.what() << std::endl;
        _catchErrors = true;
    }
}

void RayTracer::Core::Core::goUp()
{
    RayTracer::Core::IEntity *camera = nullptr;

    try {
        std::unique_ptr<Scene> &scene = _sceneManager.getCurrentScene();
        camera = scene->getActualCamera();
        if (camera != nullptr) {
            camera->translate(RayTracer::Shared::Vec3(0, 0, 1));
            _imageUpdated = true;
        }
    } catch (const RayTracer::Shared::CustomError &e) {
        std::cerr << e.what() << std::endl;
        _catchErrors = true;
    }
}

void RayTracer::Core::Core::goDown()
{
    RayTracer::Core::IEntity *camera = nullptr;

    try {
        std::unique_ptr<Scene> &scene = _sceneManager.getCurrentScene();
        camera = scene->getActualCamera();
        if (camera != nullptr) {
            camera->translate(RayTracer::Shared::Vec3(0, 0, -1));
            _imageUpdated = true;
        }
    } catch (const RayTracer::Shared::CustomError &e) {
        std::cerr << e.what() << std::endl;
        _catchErrors = true;
    }
}

void RayTracer::Core::Core::lookLeft()
{
    RayTracer::Core::IEntity *camera = nullptr;

    try {
        std::unique_ptr<Scene> &scene = _sceneManager.getCurrentScene();
        camera = scene->getActualCamera();
        if (camera != nullptr) {
            camera->rotate(RayTracer::Shared::Vec3(10, 0, 0));
            _imageUpdated = true;
        }
    } catch (const RayTracer::Shared::CustomError &e) {
        std::cerr << e.what() << std::endl;
        _catchErrors = true;
    }
}

void RayTracer::Core::Core::lookRight()
{
    RayTracer::Core::IEntity *camera = nullptr;

    try {
        std::unique_ptr<Scene> &scene = _sceneManager.getCurrentScene();
        camera = scene->getActualCamera();
        if (camera != nullptr) {
            camera->rotate(RayTracer::Shared::Vec3(-10, 0, 0));
            _imageUpdated = true;
        }
    } catch (const RayTracer::Shared::CustomError &e) {
        std::cerr << e.what() << std::endl;
        _catchErrors = true;
    }
}

void RayTracer::Core::Core::lookUp()
{
    RayTracer::Core::IEntity *camera = nullptr;

    try {
        std::unique_ptr<Scene> &scene = _sceneManager.getCurrentScene();
        camera = scene->getActualCamera();
        if (camera != nullptr) {
            camera->rotate(RayTracer::Shared::Vec3(0, -15, 0));
            _imageUpdated = true;
        }
    } catch (const RayTracer::Shared::CustomError &e) {
        std::cerr << e.what() << std::endl;
        _catchErrors = true;
    }
}

void RayTracer::Core::Core::lookDown()
{
    RayTracer::Core::IEntity *camera = nullptr;

    try {
        std::unique_ptr<Scene> &scene = _sceneManager.getCurrentScene();
        camera = scene->getActualCamera();
        if (camera != nullptr) {
            camera->rotate(RayTracer::Shared::Vec3(0, 15, 0));
            _imageUpdated = true;
        }
    } catch (const RayTracer::Shared::CustomError &e) {
        std::cerr << e.what() << std::endl;
        _catchErrors = true;
    }
}

void RayTracer::Core::Core::goNextCamera()
{
    try {
        std::unique_ptr <Scene> &scene = _sceneManager.getCurrentScene();
        scene->setNextCamera();
    } catch (const RayTracer::Shared::ConfigError &e) {
        _catchErrors = true;
    }
}

void RayTracer::Core::Core::goPreviousCamera()
{
    try {
        std::unique_ptr <Scene> &scene = _sceneManager.getCurrentScene();
        scene->setPreviousCamera();
    } catch (const RayTracer::Shared::ConfigError &e) {
        std::cerr << e.what() << std::endl;
        _catchErrors = true;
    }
}

void RayTracer::Core::Core::goNextScene()
{
    try {
        _sceneManager.setNextScene();
        std::unique_ptr<Scene> &new_scene = _sceneManager.getCurrentScene();
        new_scene->init(_pluginLoader.getFactories(), _pluginLoader.getLibraries());
        _imageUpdated = true;
    } catch (const RayTracer::Shared::ConfigError &e) {
        std::cerr << e.what() << std::endl;
        _catchErrors = true;
        _sceneManager.setPreviousScene();
        return;
    } catch (const RayTracer::Shared::SettingWrapper::NotFoundException &e) {
        std::cerr << e.what() << std::endl;
        _catchErrors = true;
        _sceneManager.setPreviousScene();
        return;
    }
    _sceneManager.setPreviousScene();
    try {
        std::unique_ptr<Scene> &old_scene = _sceneManager.getCurrentScene();
        old_scene->close();
    } catch (const RayTracer::Shared::CustomError &e) {
        std::cerr << e.what() << std::endl;
        _catchErrors = true;
    }
    _sceneManager.setNextScene();
}

void RayTracer::Core::Core::goPreviousScene()
{
    try {
        _sceneManager.setPreviousScene();
        std::unique_ptr<Scene> &new_scene = _sceneManager.getCurrentScene();
        new_scene->init(_pluginLoader.getFactories(), _pluginLoader.getLibraries());
        _imageUpdated = true;
    } catch (const RayTracer::Shared::ConfigError &e) {
        std::cerr << e.what() << std::endl;
        _catchErrors = true;
        _sceneManager.setPreviousScene();
        return;
    } catch (const RayTracer::Shared::SettingWrapper::NotFoundException &e) {
        std::cerr << e.what() << std::endl;
        _catchErrors = true;
        _sceneManager.setPreviousScene();
        return;
    }
    _sceneManager.setNextScene();
    try {
        std::unique_ptr<Scene> &old_scene = _sceneManager.getCurrentScene();
        old_scene->close();
    } catch (const RayTracer::Shared::CustomError &e) {
        std::cerr << e.what() << std::endl;
        _catchErrors = true;
    }
    _sceneManager.setPreviousScene();
}

void RayTracer::Core::Core::manageRenderingPercentage()
{
    if (_renderingPercentage == 1)
        _renderingPercentage = 0.2;
    else
        _renderingPercentage = 1;
    _imageUpdated = true;
}

void RayTracer::Core::Core::setGraphModule(RayTracer::Plugins::Graphics::IGraphModule* graphModule)
{
    _graphModule = graphModule;
}

void RayTracer::Core::Core::setAmbientLight(float ambientLight)
{
    if (ambientLight < 0)
        ambientLight = 0;
    else if (ambientLight > 1)
        ambientLight = 1;
    else
        _ambientLight = ambientLight;
}

float RayTracer::Core::Core::getAmbientLight() const
{
    return _ambientLight;
}