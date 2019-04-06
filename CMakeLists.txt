cmake_minimum_required(VERSION 3.13)
set(PROJECT_NAME TowerDefense)

project(${PROJECT_NAME})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -static")
set(CMAKE_CXX_STANDARD 14)

add_executable(${PROJECT_NAME} src/main.cpp src/util/tween/Properties.h src/util/tween/Properties.cpp src/util/Util.h src/util/tween/Ease.cpp src/util/tween/Ease.h src/util/tween/Tween.h src/util/Definitions.h src/engine/states/State.h src/engine/StateHandler.cpp src/engine/StateHandler.h src/engine/AssetHandler.h src/engine/AssetHandler.cpp src/engine/InputHandler.cpp src/engine/InputHandler.h src/Game.cpp src/Game.h src/engine/states/SplashState.h src/engine/states/SplashState.cpp)

set(SFML_STATIC_LIBRARIES TRUE)

find_package(SFML 2 COMPONENTS graphics audio REQUIRED)
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-audio)