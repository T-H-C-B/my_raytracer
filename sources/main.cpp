//
// Created by Theophilus Homawoo on 15/04/2023.
//

#include "main.hpp"

mainTest::mainTest() {
    std::cout << "Hello, World!" << std::endl;
}

mainTest::~mainTest() {
    std::cout << "Goodbye, World!" << std::endl;
}

void mainTest::run() {
    SceneLoader sceneLoader("config.json", "./plugins");
    sceneLoader.loadScene();
    sceneLoader.run();
}


int main(int argc, char** argv) {
    mainTest main;
    main.run();
    return 0;
}

